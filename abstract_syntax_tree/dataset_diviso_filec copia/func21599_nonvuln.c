xmlTextReaderHasAttributes(xmlTextReaderPtr reader) {
    xmlNodePtr node;
    if (reader == NULL)
	return(-1);
    if (reader->node == NULL)
	return(0);
    if (reader->curnode != NULL)
	node = reader->curnode;
    else
	node = reader->node;

    if ((node->type == XML_ELEMENT_NODE) &&
	((node->properties != NULL) || (node->nsDef != NULL)))
	return(1);
    
    return(0);
}