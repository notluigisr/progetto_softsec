xmlXPtrEvalXPointer(xmlXPathParserContextPtr ctxt) {
    if (ctxt->valueTab == NULL) {
	
	ctxt->valueTab = (xmlXPathObjectPtr *) 
			 xmlMalloc(10 * sizeof(xmlXPathObjectPtr));
	if (ctxt->valueTab == NULL) {
	    xmlXPtrErrMemory("STR");
	    return;
	}
	ctxt->valueNr = 0;
	ctxt->valueMax = 10;
	ctxt->value = NULL;
    }
    SKIP_BLANKS;
    if (CUR == '/') {
	xmlXPathRoot(ctxt);
        xmlXPtrEvalChildSeq(ctxt, NULL);
    } else {
	xmlChar *name;

	name = xmlXPathParseName(ctxt);
	if (name == NULL)
	    XP_ERROR(XPATH_EXPR_ERROR);
	if (CUR == '(') {
	    xmlXPtrEvalFullXPtr(ctxt, name);
	    
	    return;
	} else {
	    
	    xmlXPtrEvalChildSeq(ctxt, name);
	}
    }
    SKIP_BLANKS;
    if (CUR != 0)
	XP_ERROR(XPATH_EXPR_ERROR);
}