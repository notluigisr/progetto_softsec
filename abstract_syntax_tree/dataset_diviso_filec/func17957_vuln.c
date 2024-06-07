xsltGenerateIdFunction(xmlXPathParserContextPtr ctxt, int nargs){
    xmlNodePtr cur = NULL;
    unsigned long val;
    xmlChar str[20];

    if (nargs == 0) {
	cur = ctxt->context->node;
    } else if (nargs == 1) {
	xmlXPathObjectPtr obj;
	xmlNodeSetPtr nodelist;
	int i, ret;

	if ((ctxt->value == NULL) || (ctxt->value->type != XPATH_NODESET)) {
	    ctxt->error = XPATH_INVALID_TYPE;
	    xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"STR");
	    return;
	}
	obj = valuePop(ctxt);
	nodelist = obj->nodesetval;
	if ((nodelist == NULL) || (nodelist->nodeNr <= 0)) {
	    xmlXPathFreeObject(obj);
	    valuePush(ctxt, xmlXPathNewCString(""));
	    return;
	}
	cur = nodelist->nodeTab[0];
	for (i = 1;i < nodelist->nodeNr;i++) {
	    ret = xmlXPathCmpNodes(cur, nodelist->nodeTab[i]);
	    if (ret == -1)
	        cur = nodelist->nodeTab[i];
	}
	xmlXPathFreeObject(obj);
    } else {
	xsltTransformError(xsltXPathGetTransformContext(ctxt), NULL, NULL,
		"STR", nargs);
	ctxt->error = XPATH_INVALID_ARITY;
	return;
    }
    
    val = (unsigned long)((char *)cur - (char *)0);
    val /= sizeof(xmlNode);
    sprintf((char *)str, "STR", val);
    valuePush(ctxt, xmlXPathNewString(str));
}