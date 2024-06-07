xmlPushInput(xmlParserCtxtPtr ctxt, xmlParserInputPtr input) {
    int ret;
    if (input == NULL) return(-1);

    if (xmlParserDebugEntities) {
	if ((ctxt->input != NULL) && (ctxt->input->filename))
	    xmlGenericError(xmlGenericErrorContext,
		    "STR", ctxt->input->filename,
		    ctxt->input->line);
	xmlGenericError(xmlGenericErrorContext,
		"STR", ctxt->inputNr+1, input->cur);
    }
    ret = inputPush(ctxt, input);
    if (ctxt->instate == XML_PARSER_EOF)
        return(-1);
    GROW;
    return(ret);
}