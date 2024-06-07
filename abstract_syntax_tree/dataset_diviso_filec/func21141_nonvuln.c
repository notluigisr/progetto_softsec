int32_t ZRtp::compareCommit(ZrtpPacketCommit *commit) {
    
    
    int32_t len = 0;
    len = !multiStream ? HVI_SIZE : (4 * ZRTP_WORD_SIZE);
    return (memcmp(hvi, commit->getHvi(), len));
}