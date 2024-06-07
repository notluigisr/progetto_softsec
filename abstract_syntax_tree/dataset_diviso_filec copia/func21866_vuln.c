    void reset(){
        flags =0;
        for (std::vector<DRW_Variant*>::iterator it=extData.begin(); it!=extData.end(); ++it)
            delete *it;
        extData.clear();
    }