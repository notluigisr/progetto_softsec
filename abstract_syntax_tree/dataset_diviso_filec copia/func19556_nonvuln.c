xmlParseAttValue(xmlParserCtxtPtr ctxt) {
    if ((ctxt == NULL) || (ctxt->input == NULL)) return(NULL);
    return(xmlParseAttValueInternal(ctxt, NULL, NULL, 0));
}