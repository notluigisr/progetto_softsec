xmlMemUsed(void) {
    int res;

    xmlMutexLock(xmlMemMutex);
    res = debugMemSize;
    xmlMutexUnlock(xmlMemMutex);
    return(res);
}