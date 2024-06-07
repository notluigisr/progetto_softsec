xsltParseAttrXSLTVersion(xsltCompilerCtxtPtr cctxt, xmlNodePtr node,
			 int instrCategory)
{
    xmlChar *value;
    xmlAttrPtr attr;

    if ((cctxt == NULL) || (node == NULL))
	return(-1);

    if (instrCategory == XSLT_ELEMENT_CATEGORY_XSLT)
	attr = xmlHasNsProp(node, BAD_CAST "STR", NULL);
    else
	attr = xmlHasNsProp(node, BAD_CAST "STR", XSLT_NAMESPACE);

    if (attr == NULL)
	return(0);

    attr->psvi = (void *) xsltXSLTAttrMarker;

    if ((attr->children != NULL) &&
	(attr->children->content != NULL))
	value = attr->children->content;
    else {
	xsltTransformError(NULL, cctxt->style, node,
	    "STR");
	cctxt->style->errors++;
	return(1);
    }

    if (! xmlStrEqual(value, (const xmlChar *)"STR")) {
	cctxt->inode->forwardsCompat = 1;
	
	
	if (! cctxt->hasForwardsCompat) {
	    cctxt->hasForwardsCompat = 1;
	    cctxt->errSeverity = XSLT_ERROR_SEVERITY_WARNING;
	    xsltTransformError(NULL, cctxt->style, node,
		"STR"
		"STR"
		"STR"
		"STR");
	    cctxt->style->warnings++;
	    cctxt->errSeverity = XSLT_ERROR_SEVERITY_ERROR;
	}
    } else {
	cctxt->inode->forwardsCompat = 0;
    }

    if (attr && (instrCategory == XSLT_ELEMENT_CATEGORY_LRE)) {
	
	attr->psvi = (void *) xsltXSLTAttrMarker;
    }
    return(1);
}