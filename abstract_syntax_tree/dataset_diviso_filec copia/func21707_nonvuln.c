xmlStaticCopyNodeList(xmlNodePtr node, xmlDocPtr doc, xmlNodePtr parent) {
    xmlNodePtr ret = NULL;
    xmlNodePtr p = NULL,q;

    while (node != NULL) {
#ifdef LIBXML_TREE_ENABLED
	if (node->type == XML_DTD_NODE ) {
	    if (doc == NULL) {
		node = node->next;
		continue;
	    }
	    if (doc->intSubset == NULL) {
		q = (xmlNodePtr) xmlCopyDtd( (xmlDtdPtr) node );
		if (q == NULL) return(NULL);
		q->doc = doc;
		q->parent = parent;
		doc->intSubset = (xmlDtdPtr) q;
		xmlAddChild(parent, q);
	    } else {
		q = (xmlNodePtr) doc->intSubset;
		xmlAddChild(parent, q);
	    }
	} else
#endif 
	    q = xmlStaticCopyNode(node, doc, parent, 1);
	if (q == NULL) return(NULL);
	if (ret == NULL) {
	    q->prev = NULL;
	    ret = p = q;
	} else if (p != q) {
	
	    p->next = q;
	    q->prev = p;
	    p = q;
	}
	node = node->next;
    }
    return(ret);
}