xmlTextReaderConstNamespaceUri(xmlTextReaderPtr reader) {
    xmlNodePtr node;
    if ((reader == NULL) || (reader->node == NULL))
	return(NULL);
    if (reader->curnode != NULL)
	node = reader->curnode;
    else
	node = reader->node;
    if (node->type == XML_NAMESPACE_DECL)
	return(CONSTSTR(BAD_CAST "STR"));
    if ((node->type != XML_ELEMENT_NODE) &&
	(node->type != XML_ATTRIBUTE_NODE))
	return(NULL);
    if (node->ns != NULL)
	return(CONSTSTR(node->ns->href));
    return(NULL);
}