void ZrtpStateClass::evWaitConfirm2(void) {

    DEBUGOUT((cout << "STR"));

    char *msg, first, secondLast, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        secondLast = tolower(*(msg+6));
        last = tolower(*(msg+7));

        
        if ((first == 'd' && secondLast == '2') || (multiStream && (first == 'c' && last == ' '))) {
            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();             
            }
            return;
        }
        
        if (first == 'c' && last == '2') {
            ZrtpPacketConfirm cpkt(pkt);
            ZrtpPacketConf2Ack* confack = parent->prepareConf2Ack(&cpkt, &errorCode);

            
            if (confack == NULL) {
                sendErrorPacket(errorCode);
                return;
            }
            sentPacket = static_cast<ZrtpPacketBase *>(confack);

            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();             
                return;
            }
            if (!parent->srtpSecretsReady(ForReceiver) || !parent->srtpSecretsReady(ForSender))  {
                parent->sendInfo(Severe, CriticalSWError);
                sendErrorPacket(CriticalSWError);
                return;
            }
            nextState(SecureState);
            parent->sendInfo(Info, InfoSecureStateOn);
        }
    }
    else {  
        if (event->type != ZrtpClose) {
            parent->zrtpNegotiationFailed(Severe, SevereProtocolError);
        }
        sentPacket = NULL;
        nextState(Initial);
    }
}