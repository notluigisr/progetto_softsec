 */
static int
xmlXPathRunEval(xmlXPathParserContextPtr ctxt, int toBool)
{
    xmlXPathCompExprPtr comp;

    if ((ctxt == NULL) || (ctxt->comp == NULL))
	return(-1);

    if (ctxt->valueTab == NULL) {
	
	ctxt->valueTab = (xmlXPathObjectPtr *)
			 xmlMalloc(10 * sizeof(xmlXPathObjectPtr));
	if (ctxt->valueTab == NULL) {
	    xmlXPathPErrMemory(ctxt, "STR");
	    xmlFree(ctxt);
	}
	ctxt->valueNr = 0;
	ctxt->valueMax = 10;
	ctxt->value = NULL;
    }
#ifdef XPATH_STREAMING
    if (ctxt->comp->stream) {
	int res;

	if (toBool) {
	    
	    res = xmlXPathRunStreamEval(ctxt->context,
		ctxt->comp->stream, NULL, 1);
	    if (res != -1)
		return(res);
	} else {
	    xmlXPathObjectPtr resObj = NULL;

	    
	    res = xmlXPathRunStreamEval(ctxt->context,
		ctxt->comp->stream, &resObj, 0);

	    if ((res != -1) && (resObj != NULL)) {
		valuePush(ctxt, resObj);
		return(0);
	    }
	    if (resObj != NULL)
		xmlXPathReleaseObject(ctxt->context, resObj);
	}
	
    }
#endif
    comp = ctxt->comp;
    if (comp->last < 0) {
	xmlGenericError(xmlGenericErrorContext,
	    "STR");
	return(-1);
    }
    if (toBool)
	return(xmlXPathCompOpEvalToBoolean(ctxt,
	    &comp->steps[comp->last], 0));
    else
	xmlXPathCompOpEval(ctxt, &comp->steps[comp->last]);
