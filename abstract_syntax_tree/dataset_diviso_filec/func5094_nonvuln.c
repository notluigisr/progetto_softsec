xmlOutputBufferCreateFile(FILE *file, xmlCharEncodingHandlerPtr encoder) {
    xmlOutputBufferPtr ret;

    if (xmlOutputCallbackInitialized == 0)
	xmlRegisterDefaultOutputCallbacks();

    if (file == NULL) return(NULL);

    ret = xmlAllocOutputBufferInternal(encoder);
    if (ret != NULL) {
        ret->context = file;
	ret->writecallback = xmlFileWrite;
	ret->closecallback = xmlFileFlush;
    }

    return(ret);
}