bool dwgReader21::readDwgTables(DRW_Header& hdr) {
    DRW_DBG("STR");
    dwgSectionInfo si = sections[secEnum::OBJECTS];
    if (si.Id<0)
        return false;

    DRW_DBG("STR");
    dataSize = si.size;
    objData.reset( new duint8 [dataSize] );
    bool ret = dwgReader21::parseDataPage(si, objData.get());
    if (!ret)
        return ret;

    DRW_DBG("STR");
    dwgBuffer dataBuf(objData.get(), dataSize, &decoder);
    ret = dwgReader::readDwgTables(hdr, &dataBuf);

    return ret;
}