xmlCharEncCloseFunc(xmlCharEncodingHandler *handler) {
    int ret = 0;
    int tofree = 0;
    if (handler == NULL) return(-1);
    if (handler->name == NULL) return(-1);
#ifdef LIBXML_ICONV_ENABLED
    
    if ((handler->iconv_out != NULL) || (handler->iconv_in != NULL)) {
        tofree = 1;
	if (handler->iconv_out != NULL) {
	    if (iconv_close(handler->iconv_out))
		ret = -1;
	    handler->iconv_out = NULL;
	}
	if (handler->iconv_in != NULL) {
	    if (iconv_close(handler->iconv_in))
		ret = -1;
	    handler->iconv_in = NULL;
	}
    }
#endif 
#ifdef LIBXML_ICU_ENABLED
    if ((handler->uconv_out != NULL) || (handler->uconv_in != NULL)) {
        tofree = 1;
	if (handler->uconv_out != NULL) {
	    closeIcuConverter(handler->uconv_out);
	    handler->uconv_out = NULL;
	}
	if (handler->uconv_in != NULL) {
	    closeIcuConverter(handler->uconv_in);
	    handler->uconv_in = NULL;
	}
    }
#endif
    if (tofree) {
        
        if (handler->name != NULL)
            xmlFree(handler->name);
        handler->name = NULL;
        xmlFree(handler);
    }
#ifdef DEBUG_ENCODING
    if (ret)
        xmlGenericError(xmlGenericErrorContext,
		"STR");
    else
        xmlGenericError(xmlGenericErrorContext,
		"STR");
#endif

    return(ret);
}