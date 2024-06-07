xmlTextReaderConstPrefix(xmlTextReaderPtr reader) {
    xmlNodePtr node;
    if ((reader == NULL) || (reader->node == NULL))
	return(NULL);
    if (reader->curnode != NULL)
	node = reader->curnode;
    else
	node = reader->node;
    if (node->type == XML_NAMESPACE_DECL) {
	xmlNsPtr ns = (xmlNsPtr) node;
	if (ns->prefix == NULL)
	    return(NULL);
	return(CONSTSTR(BAD_CAST "STR"));
    }
    if ((node->type != XML_ELEMENT_NODE) &&
	(node->type != XML_ATTRIBUTE_NODE))
	return(NULL);
    if ((node->ns != NULL) && (node->ns->prefix != NULL))
	return(CONSTSTR(node->ns->prefix));
    return(NULL);
}