bool dwgReader18::readDwgHandles() {
    DRW_DBG("STR");
    dwgSectionInfo si = sections[secEnum::HANDLES];
    if (si.Id<0)
        return false;

    if (!parseDataPage(si)) {
        return false;
    }

    
    uncompSize=si.size;
    dwgBuffer dataBuf(objData.get(), uncompSize, &decoder);

    bool ret {dwgReader::readDwgHandles(&dataBuf, 0, si.size)};

    
    if (objData){
        objData.reset();
        uncompSize = 0;
    }

    return ret;
}