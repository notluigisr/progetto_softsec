    DRW_TableEntry(const DRW_TableEntry& e) {
        tType = e.tType;
        handle = e.handle;
        parentHandle = e.parentHandle;
        name = e.name;
        flags = e.flags;
        numReactors = e.numReactors;
        xDictFlag = e.xDictFlag;
        curr = e.curr;
        for (std::vector<DRW_Variant*>::const_iterator it=e.extData.begin(); it!=e.extData.end(); ++it){
            extData.push_back(new DRW_Variant(*(*it)));
        }
    }