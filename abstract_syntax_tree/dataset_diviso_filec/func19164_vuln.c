 */
static xmlXPathParserContextPtr
xmlXPathCompParserContext(xmlXPathCompExprPtr comp, xmlXPathContextPtr ctxt) {
    xmlXPathParserContextPtr ret;

    ret = (xmlXPathParserContextPtr) xmlMalloc(sizeof(xmlXPathParserContext));
    if (ret == NULL) {
        xmlXPathErrMemory(ctxt, "STR");
	return(NULL);
    }
    memset(ret, 0 , (size_t) sizeof(xmlXPathParserContext));

    
    ret->valueTab = (xmlXPathObjectPtr *)
                     xmlMalloc(10 * sizeof(xmlXPathObjectPtr));
    if (ret->valueTab == NULL) {
	xmlFree(ret);
	xmlXPathErrMemory(ctxt, "STR");
	return(NULL);
    }
    ret->valueNr = 0;
    ret->valueMax = 10;
    ret->value = NULL;

    ret->context = ctxt;
    ret->comp = comp;
