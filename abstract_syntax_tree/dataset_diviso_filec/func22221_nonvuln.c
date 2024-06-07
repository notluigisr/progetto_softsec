ResizableByteBufferListNode* VP8ComponentDecoder::SendToVirtualThread::read(Sirikata::MuxReader&reader, uint8_t stream_id) {
    using namespace Sirikata;
    always_assert(stream_id < sizeof(vbuffers) / sizeof(vbuffers[0]) &&
                  "STR");
    if (!vbuffers[stream_id].empty()) {
        auto retval = vbuffers[stream_id].front();
        if (retval->size() == 0) {
            always_assert(eof);
        } else { 
            vbuffers[stream_id].pop();
        }
        return retval;
    }
    if (eof) {
        always_assert(false);
        return NULL;
    }
    while (!eof) {
        ResizableByteBufferListNode *data = new ResizableByteBufferListNode;
        auto ret = reader.nextDataPacket(*data);
        if (ret.second != JpegError::nil()) {
            set_eof();
            break;
        }
        data->stream_id = ret.first;
        bool buffer_it = ret.first != stream_id;
        if (buffer_it) {
            send(data);
        } else {
            return data;
        }
    }
    if (!vbuffers[stream_id].empty()) {
        auto retval = vbuffers[stream_id].front();
        if (retval->size() == 0) {
            always_assert(eof);
        } else { 
            vbuffers[stream_id].pop();
        }
        return retval;
    }
    return NULL;
}