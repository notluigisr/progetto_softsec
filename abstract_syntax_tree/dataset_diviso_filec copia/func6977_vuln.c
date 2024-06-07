CotpConnection_readToTpktBuffer(CotpConnection* self)
{
    uint8_t* buffer = self->readBuffer->buffer;
    int bufferSize = self->readBuffer->maxSize;
    int bufPos = self->readBuffer->size;

    assert (bufferSize > 4);

    int readBytes;

    if (bufPos < 4) {

        readBytes = readFromSocket(self, buffer + bufPos, 4 - bufPos);

        if (readBytes < 0)
            goto exit_closed;

        if (DEBUG_COTP) {
            if (readBytes > 0)
                printf("STR", readBytes);
        }

        bufPos += readBytes;

        if (bufPos == 4) {
            if ((buffer[0] == 3) && (buffer[1] == 0)) {
                self->packetSize = (buffer[2] * 0x100) + buffer[3];

                if (DEBUG_COTP)
                    printf("STR", self->packetSize);

                if (self->packetSize > bufferSize) {
                    if (DEBUG_COTP) printf("STR");
                    goto exit_error;
                }
            }
            else {
                if (DEBUG_COTP) printf("STR");
                goto exit_error;
            }
        }
        else
            goto exit_waiting;
    }

    readBytes = readFromSocket(self, buffer + bufPos, self->packetSize - bufPos);

    if (readBytes < 0)
        goto exit_closed;

    bufPos += readBytes;

    if (bufPos < self->packetSize)
       goto exit_waiting;

    if (DEBUG_COTP) printf("STR", self->packetSize);

    self->readBuffer->size = bufPos;
    return TPKT_PACKET_COMPLETE;

exit_closed:
    if (DEBUG_COTP) printf("STR");
    return TPKT_ERROR;

exit_error:
    if (DEBUG_COTP) printf("STR");
    return TPKT_ERROR;

exit_waiting:

    if (DEBUG_COTP)
        if (bufPos != 0)
            printf("STR", bufPos, self->packetSize);

    self->readBuffer->size = bufPos;
    return TPKT_WAITING;
}