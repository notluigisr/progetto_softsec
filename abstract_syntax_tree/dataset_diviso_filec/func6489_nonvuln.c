xmlTextReaderNext(xmlTextReaderPtr reader) {
    int ret;
    xmlNodePtr cur;

    if (reader == NULL)
	return(-1);
    if (reader->doc != NULL)
        return(xmlTextReaderNextTree(reader));
    cur = reader->node;
    if ((cur == NULL) || (cur->type != XML_ELEMENT_NODE))
        return(xmlTextReaderRead(reader));
    if (reader->state == XML_TEXTREADER_END || reader->state == XML_TEXTREADER_BACKTRACK)
        return(xmlTextReaderRead(reader));
    if (cur->extra & NODE_IS_EMPTY)
        return(xmlTextReaderRead(reader));
    do {
        ret = xmlTextReaderRead(reader);
	if (ret != 1)
	    return(ret);
    } while (reader->node != cur);
    return(xmlTextReaderRead(reader));
}