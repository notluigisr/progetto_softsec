void dwgReader18::parseSysPage(duint8 *decompSec, duint32 decompSize){
    DRW_DBG("STR");
    duint32 compSize = fileBuf->getRawLong32();
    DRW_DBG("STR"); DRW_DBGH(compSize);
    DRW_DBG("STR"); DRW_DBGH(fileBuf->getRawLong32());
    DRW_DBG("STR");

    duint8 hdrData[20];
    fileBuf->moveBitPos(-160);
    fileBuf->getBytes(hdrData, 20);
    for (duint8 i= 16; i<20; ++i)
        hdrData[i]=0;
    duint32 calcsH = checksum(0, hdrData, 20);
    DRW_DBG("STR"); DRW_DBGH(calcsH);
    std::vector<duint8> tmpCompSec(compSize);
    fileBuf->getBytes(tmpCompSec.data(), compSize);
    duint32 calcsD = checksum(calcsH, tmpCompSec.data(), compSize);
    DRW_DBG("STR");

#ifdef DRW_DBG_DUMP
    for (unsigned int i=0, j=0; i< compSize;i++) {
        DRW_DBGH( (unsigned char)compSec[i]);
        if (j == 7) { DRW_DBG("STR"); j = 0;
        } else { DRW_DBG("STR"); j++; }
    } DRW_DBG("STR");
#endif
    DRW_DBG("STR");
    dwgCompressor comp;
    comp.decompress18(tmpCompSec.data(), decompSec, compSize, decompSize);
#ifdef DRW_DBG_DUMP
    for (unsigned int i=0, j=0; i< decompSize;i++) {
        DRW_DBGH( decompSec[i]);
        if (j == 7) { DRW_DBG("STR"); j = 0;
        } else { DRW_DBG("STR"); j++; }
    } DRW_DBG("STR");
#endif
}