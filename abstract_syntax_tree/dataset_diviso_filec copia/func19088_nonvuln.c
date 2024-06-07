__xmlParserInputBufferCreateFilename(const char *URI, xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;
    int i = 0;
    void *context = NULL;

    if (xmlInputCallbackInitialized == 0)
	xmlRegisterDefaultInputCallbacks();

    if (URI == NULL) return(NULL);

    
    if (context == NULL) {
	for (i = xmlInputCallbackNr - 1;i >= 0;i--) {
	    if ((xmlInputCallbackTable[i].matchcallback != NULL) &&
		(xmlInputCallbackTable[i].matchcallback(URI) != 0)) {
		context = xmlInputCallbackTable[i].opencallback(URI);
		if (context != NULL) {
		    break;
		}
	    }
	}
    }
    if (context == NULL) {
	return(NULL);
    }

    
    ret = xmlAllocParserInputBuffer(enc);
    if (ret != NULL) {
	ret->context = context;
	ret->readcallback = xmlInputCallbackTable[i].readcallback;
	ret->closecallback = xmlInputCallbackTable[i].closecallback;
#ifdef HAVE_ZLIB_H
	if ((xmlInputCallbackTable[i].opencallback == xmlGzfileOpen) &&
		(strcmp(URI, "STR") != 0)) {
#if defined(ZLIB_VERNUM) && ZLIB_VERNUM >= 0x1230
            ret->compressed = !gzdirect(context);
#else
	    if (((z_stream *)context)->avail_in > 4) {
	        char *cptr, buff4[4];
		cptr = (char *) ((z_stream *)context)->next_in;
		if (gzread(context, buff4, 4) == 4) {
		    if (strncmp(buff4, cptr, 4) == 0)
		        ret->compressed = 0;
		    else
		        ret->compressed = 1;
		    gzrewind(context);
		}
	    }
#endif
	}
#endif
#ifdef LIBXML_LZMA_ENABLED
	if ((xmlInputCallbackTable[i].opencallback == xmlXzfileOpen) &&
		(strcmp(URI, "STR") != 0)) {
            ret->compressed = __libxml2_xzcompressed(context);
	}
#endif
    }
    else
      xmlInputCallbackTable[i].closecallback (context);

    return(ret);
}