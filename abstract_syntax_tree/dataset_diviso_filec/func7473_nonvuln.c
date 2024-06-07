xsltCompilerNodePop(xsltCompilerCtxtPtr cctxt, xmlNodePtr node)
{    
    if (cctxt->inode == NULL) {
	xmlGenericError(xmlGenericErrorContext,
	    "STR");
	return;
    }
    
    if (cctxt->inode->node != node) {
	xmlGenericError(xmlGenericErrorContext,
	"STR");
	goto mismatch;
    }
    if (cctxt->inode->depth != cctxt->depth) {
	xmlGenericError(xmlGenericErrorContext,
	"STR");
	goto mismatch;
    }
    
    if ((cctxt->ivar) && (cctxt->ivar->depth > cctxt->depth))
	xsltCompilerVarInfoPop(cctxt);

    cctxt->depth--;
    cctxt->inode = cctxt->inode->prev;
    if (cctxt->inode != NULL)
	cctxt->inode->curChildType = 0;
    return;

mismatch:
    {
	const xmlChar *nsName = NULL, *name = NULL;
	const xmlChar *infnsName = NULL, *infname = NULL;
	
	if (node) {
	    if (node->type == XML_ELEMENT_NODE) {
		name = node->name;
		if (node->ns != NULL)
		    nsName = node->ns->href;
		else
		    nsName = BAD_CAST "";
	    } else {
		name = BAD_CAST "STR";
		nsName = BAD_CAST "";
	    }
	} else
	    name = BAD_CAST "STR";

	if (cctxt->inode->node) {
	    if (node->type == XML_ELEMENT_NODE) {
		infname = cctxt->inode->node->name;
		if (cctxt->inode->node->ns != NULL)
		    infnsName = cctxt->inode->node->ns->href;
		else
		    infnsName = BAD_CAST "";
	    } else {
		infname = BAD_CAST "STR";
		infnsName = BAD_CAST "";
	    }
	} else
	    infname = BAD_CAST "STR";

	
	xmlGenericError(xmlGenericErrorContext,
	    "STR",
	    name, nsName);
	xmlGenericError(xmlGenericErrorContext,
	    "STR",
	    infname, infnsName);
    }
}