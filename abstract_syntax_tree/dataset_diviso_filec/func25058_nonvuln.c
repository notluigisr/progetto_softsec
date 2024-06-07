xmlDocSetRootElement(xmlDocPtr doc, xmlNodePtr root) {
    xmlNodePtr old = NULL;

    if (doc == NULL) return(NULL);
    if ((root == NULL) || (root->type == XML_NAMESPACE_DECL))
	return(NULL);
    xmlUnlinkNode(root);
    xmlSetTreeDoc(root, doc);
    root->parent = (xmlNodePtr) doc;
    old = doc->children;
    while (old != NULL) {
	if (old->type == XML_ELEMENT_NODE)
	    break;
        old = old->next;
    }
    if (old == NULL) {
	if (doc->children == NULL) {
	    doc->children = root;
	    doc->last = root;
	} else {
	    xmlAddSibling(doc->children, root);
	}
    } else {
	xmlReplaceNode(old, root);
    }
    return(old);
}