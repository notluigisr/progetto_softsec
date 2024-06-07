xmlNewReconciledNs(xmlDocPtr doc, xmlNodePtr tree, xmlNsPtr ns) {
    xmlNsPtr def;
    xmlChar prefix[50];
    int counter = 1;

    if ((tree == NULL) || (tree->type != XML_ELEMENT_NODE)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"STR");
#endif
	return(NULL);
    }
    if ((ns == NULL) || (ns->type != XML_NAMESPACE_DECL)) {
#ifdef DEBUG_TREE
        xmlGenericError(xmlGenericErrorContext,
		"STR");
#endif
	return(NULL);
    }
    
    def = xmlSearchNsByHref(doc, tree, ns->href);
    if (def != NULL)
        return(def);

    
    if (ns->prefix == NULL)
	snprintf((char *) prefix, sizeof(prefix), "STR");
    else
	snprintf((char *) prefix, sizeof(prefix), "STR", (char *)ns->prefix);

    def = xmlSearchNs(doc, tree, prefix);
    while (def != NULL) {
        if (counter > 1000) return(NULL);
	if (ns->prefix == NULL)
	    snprintf((char *) prefix, sizeof(prefix), "STR", counter++);
	else
	    snprintf((char *) prefix, sizeof(prefix), "STR",
		(char *)ns->prefix, counter++);
	def = xmlSearchNs(doc, tree, prefix);
    }

    
    def = xmlNewNs(tree, ns->href, prefix);
    return(def);
}