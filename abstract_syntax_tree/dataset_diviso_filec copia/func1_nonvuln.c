xmlIsStreaming(xmlValidCtxtPtr ctxt) {
    xmlParserCtxtPtr pctxt;

    if (ctxt == NULL)
        return(0);
    
    if ((ctxt->finishDtd != XML_CTXT_FINISH_DTD_0) &&
        (ctxt->finishDtd != XML_CTXT_FINISH_DTD_1))
        return(0);
    pctxt = ctxt->userData;
    return(pctxt->parseMode == XML_PARSE_READER);
}