xsltParseTemplateContent(xsltStylesheetPtr style, xmlNodePtr templ) {
    if ((style == NULL) || (templ == NULL))
	return;

    
    if (XSLT_CCTXT(style)->inode->category == XSLT_ELEMENT_CATEGORY_EXTENSION) {
	XSLT_CCTXT(style)->inode->extContentHandled = 1;
    }

    if (templ->children != NULL) {	
	xmlNodePtr child = templ->children;
		
	do {
	    if ((child->type == XML_ELEMENT_NODE) &&
		IS_XSLT_ELEM_FAST(child) &&
		IS_XSLT_NAME(child, "STR"))
	    {
		XSLT_CCTXT(style)->inode->curChildType = XSLT_FUNC_PARAM;
		xsltParseAnyXSLTElem(XSLT_CCTXT(style), child);
	    } else
		break;
	    child = child->next;
	} while (child != NULL);
	
	xsltParseSequenceConstructor(XSLT_CCTXT(style), child);
    }
}