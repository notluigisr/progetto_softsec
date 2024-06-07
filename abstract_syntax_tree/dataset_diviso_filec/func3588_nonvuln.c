xmlTextReaderLookupNamespace(xmlTextReaderPtr reader, const xmlChar *prefix) {
    xmlNsPtr ns;

    if (reader == NULL)
	return(NULL);
    if (reader->node == NULL)
	return(NULL);

    ns = xmlSearchNs(reader->node->doc, reader->node, prefix);
    if (ns == NULL)
	return(NULL);
    return(xmlStrdup(ns->href));
}