xmlRegisterOutputCallbacks(xmlOutputMatchCallback matchFunc,
	xmlOutputOpenCallback openFunc, xmlOutputWriteCallback writeFunc,
	xmlOutputCloseCallback closeFunc) {
    if (xmlOutputCallbackNr >= MAX_OUTPUT_CALLBACK) {
	return(-1);
    }
    xmlOutputCallbackTable[xmlOutputCallbackNr].matchcallback = matchFunc;
    xmlOutputCallbackTable[xmlOutputCallbackNr].opencallback = openFunc;
    xmlOutputCallbackTable[xmlOutputCallbackNr].writecallback = writeFunc;
    xmlOutputCallbackTable[xmlOutputCallbackNr].closecallback = closeFunc;
    xmlOutputCallbackInitialized = 1;
    return(xmlOutputCallbackNr++);
}