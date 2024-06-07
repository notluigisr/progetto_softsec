xmlSchemaFreeIDC(xmlSchemaIDCPtr idcDef)
{
    xmlSchemaIDCSelectPtr cur, prev;

    if (idcDef == NULL)
	return;
    if (idcDef->annot != NULL)
        xmlSchemaFreeAnnot(idcDef->annot);
    
    if (idcDef->selector != NULL) {
	if (idcDef->selector->xpathComp != NULL)
	    xmlFreePattern((xmlPatternPtr) idcDef->selector->xpathComp);
	xmlFree(idcDef->selector);
    }
    
    if (idcDef->fields != NULL) {
	cur = idcDef->fields;
	do {
	    prev = cur;
	    cur = cur->next;
	    if (prev->xpathComp != NULL)
		xmlFreePattern((xmlPatternPtr) prev->xpathComp);
	    xmlFree(prev);
	} while (cur != NULL);
    }
    xmlFree(idcDef);
}