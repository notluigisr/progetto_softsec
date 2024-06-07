AlgorithmEnum* ZRtp::findBestSASType(ZrtpPacketHello *hello) {

    int  i;
    int ii;
    int numAlgosOffered;
    AlgorithmEnum* algosOffered[ZrtpConfigure::maxNoOfAlgos+1];

    int numAlgosConf;
    AlgorithmEnum* algosConf[ZrtpConfigure::maxNoOfAlgos+1];

    int num = hello->getNumSas();
    if (num == 0) {
        return &zrtpSasTypes.getByName(mandatorySasType);
    }
    
    numAlgosConf = configureAlgos.getNumConfiguredAlgos(SasType);
    for (i = 0; i < numAlgosConf; i++) {
        algosConf[i] = &configureAlgos.getAlgoAt(SasType, i);
    }
    
    for (numAlgosOffered = 0, i = 0; i < num; i++) {
        algosOffered[numAlgosOffered] = &zrtpSasTypes.getByName((const char*)hello->getSasType(i++));
        if (!algosOffered[numAlgosOffered]->isValid())
            continue;
        numAlgosOffered++;
    }
    
    for (i = 0; i < numAlgosOffered; i++) {
        for (ii = 0; ii < numAlgosConf; ii++) {
            if (*(int32_t*)(algosOffered[i]->getName()) == *(int32_t*)(algosConf[ii]->getName())) {
                return algosConf[ii];
            }
        }
    }
    
    return &zrtpSasTypes.getByName(mandatorySasType);
}