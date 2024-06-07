ZrtpPacketPingAck* ZRtp::preparePingAck(ZrtpPacketPing* ppkt) {

    
    
    
    zrtpPingAck.setLocalEpHash(ownZid);
    zrtpPingAck.setRemoteEpHash(ppkt->getEpHash());
    zrtpPingAck.setSSRC(peerSSRC);
    return &zrtpPingAck;
}