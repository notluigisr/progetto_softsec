xmlSchemaLookupNamespace(xmlSchemaValidCtxtPtr vctxt,
			 const xmlChar *prefix)
{
    if (vctxt->sax != NULL) {
	int i, j;
	xmlSchemaNodeInfoPtr inode;

	for (i = vctxt->depth; i >= 0; i--) {
	    if (vctxt->elemInfos[i]->nbNsBindings != 0) {
		inode = vctxt->elemInfos[i];
		for (j = 0; j < inode->nbNsBindings * 2; j += 2) {
		    if (((prefix == NULL) &&
			    (inode->nsBindings[j] == NULL)) ||
			((prefix != NULL) && xmlStrEqual(prefix,
			    inode->nsBindings[j]))) {

			
			return (inode->nsBindings[j+1]);
		    }
		}
	    }
	}
	return (NULL);
#ifdef LIBXML_READER_ENABLED
    } else if (vctxt->reader != NULL) {
	xmlChar *nsName;

	nsName = xmlTextReaderLookupNamespace(vctxt->reader, prefix);
	if (nsName != NULL) {
	    const xmlChar *ret;

	    ret = xmlDictLookup(vctxt->dict, nsName, -1);
	    xmlFree(nsName);
	    return (ret);
	} else
	    return (NULL);
#endif
    } else {
	xmlNsPtr ns;

	if ((vctxt->inode->node == NULL) ||
	    (vctxt->inode->node->doc == NULL)) {
	    VERROR_INT("STR",
		"STR");
	    return (NULL);
	}
	ns = xmlSearchNs(vctxt->inode->node->doc,
	    vctxt->inode->node, prefix);
	if (ns != NULL)
	    return (ns->href);
	return (NULL);
    }
}