bool dwgReader18::parseDataPage(const dwgSectionInfo &si){
    DRW_DBG("STR");
    objData.reset( new duint8 [si.pageCount * si.maxSize] );

    for (auto it=si.pages.begin(); it!=si.pages.end(); ++it){
        dwgPageInfo pi = it->second;
        if (!fileBuf->setPosition(pi.address))
            return false;
        
        duint8 hdrData[32];
        fileBuf->getBytes(hdrData, 32);
        dwgCompressor::decrypt18Hdr(hdrData, 32, pi.address);
        DRW_DBG("STR");
        for (unsigned int i=0, j=0; i< 32;i++) {
            DRW_DBGH( static_cast<unsigned char>(hdrData[i]));
            if (j == 7) {
                DRW_DBG("STR");
                j = 0;
            } else {
                DRW_DBG("STR");
                j++;
            }
        } DRW_DBG("STR");

        DRW_DBG("STR"); DRW_DBGH(pi.Id);
        DRW_DBG("STR"); DRW_DBGH(pi.size);
        DRW_DBG("STR"); DRW_DBGH(pi.address);
        DRW_DBG("STR"); DRW_DBGH(pi.dataSize);
        DRW_DBG("STR");
        dwgBuffer bufHdr(hdrData, 32, &decoder);
        DRW_DBG("STR"); DRW_DBGH(bufHdr.getRawLong32());
        DRW_DBG("STR"); DRW_DBGH(bufHdr.getRawLong32());
        pi.cSize = bufHdr.getRawLong32();
        DRW_DBG("STR"); DRW_DBG(pi.cSize);
        pi.uSize = bufHdr.getRawLong32();
        DRW_DBG("STR"); DRW_DBG(pi.uSize);
        DRW_DBG("STR"); DRW_DBGH(bufHdr.getRawLong32());
        DRW_DBG("STR"); DRW_DBGH(bufHdr.getRawLong32());
        DRW_DBG("STR"); DRW_DBGH(bufHdr.getRawLong32());
        DRW_DBG("STR");

        
        std::vector<duint8> cData(pi.cSize);
        if (!fileBuf->setPosition(pi.address + 32)) {
            return false;
        }
        fileBuf->getBytes(cData.data(), pi.cSize);

        
        duint32 calcsD = checksum(0, cData.data(), pi.cSize);
        for (duint8 i= 24; i<28; ++i)
            hdrData[i]=0;
        duint32 calcsH = checksum(calcsD, hdrData, 32);
        DRW_DBG("STR"); DRW_DBGH(calcsH);
        DRW_DBG("STR");

        duint8* oData = objData.get() + pi.startOffset;
        pi.uSize = si.maxSize;
        DRW_DBG("STR");
        dwgCompressor comp;
        comp.decompress18(cData.data(), oData, pi.cSize, pi.uSize);
    }
    return true;
}