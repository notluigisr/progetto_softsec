bool dwgReader21::parseDataPage(const dwgSectionInfo &si, duint8 *dData){
    DRW_DBG("STR"); DRW_DBG(si.size);
    for (auto it=si.pages.begin(); it!=si.pages.end(); ++it){
        dwgPageInfo pi = it->second;
        if (!fileBuf->setPosition(pi.address))
            return false;

        std::vector<duint8> tmpPageRaw(pi.size);
        fileBuf->getBytes(&tmpPageRaw.front(), pi.size);
    #ifdef DRW_DBG_DUMP
        DRW_DBG("STR");
        for (unsigned int i=0, j=0; i< pi.size;i++) {
            DRW_DBGH( (unsigned char)tmpPageRaw[i]);
            if (j == 7) { DRW_DBG("STR"); j = 0;
            } else { DRW_DBG("STR"); j++; }
        } DRW_DBG("STR");
    #endif

        std::vector<duint8> tmpPageRS(pi.size);

        duint8 chunks =pi.size / 255;
        dwgRSCodec::decode251I(&tmpPageRaw.front(), &tmpPageRS.front(), chunks);
    #ifdef DRW_DBG_DUMP
        DRW_DBG("STR");
        for (unsigned int i=0, j=0; i< pi.size;i++) {
            DRW_DBGH( (unsigned char)tmpPageRS[i]);
            if (j == 7) { DRW_DBG("STR"); j = 0;
            } else { DRW_DBG("STR"); j++; }
        } DRW_DBG("STR");
    #endif

        DRW_DBG("STR"); DRW_DBG(pi.cSize);
        DRW_DBG("STR"); DRW_DBG(pi.startOffset);
        duint8 *pageData = dData + pi.startOffset;
        dwgCompressor::decompress21(&tmpPageRS.front(), pageData, pi.cSize, pi.uSize);

    #ifdef DRW_DBG_DUMP
        DRW_DBG("STR");
        for (unsigned int i=0, j=0; i< pi.uSize;i++) {
            DRW_DBGH( (unsigned char)pageData[i]);
            if (j == 7) { DRW_DBG("STR"); j = 0;
            } else { DRW_DBG("STR"); j++; }
        } DRW_DBG("STR");
    #endif

    }
    DRW_DBG("STR");
    return true;
}