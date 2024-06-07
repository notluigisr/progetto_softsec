xmlTextReaderGenericError(void *ctxt, xmlParserSeverities severity,
                          char *str)
{
    xmlParserCtxtPtr ctx = (xmlParserCtxtPtr) ctxt;

    xmlTextReaderPtr reader = (xmlTextReaderPtr) ctx->_private;

    if (str != NULL) {
        if (reader->errorFunc)
            reader->errorFunc(reader->errorFuncArg, str, severity,
                              (xmlTextReaderLocatorPtr) ctx);
        xmlFree(str);
    }
}