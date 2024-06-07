xhtmlIsEmpty(xmlNodePtr node) {
    if (node == NULL)
	return(-1);
    if (node->type != XML_ELEMENT_NODE)
	return(0);
    if ((node->ns != NULL) && (!xmlStrEqual(node->ns->href, XHTML_NS_NAME)))
	return(0);
    if (node->children != NULL)
	return(0);
    switch (node->name[0]) {
	case 'a':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'b':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'c':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'f':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'h':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'i':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'l':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'm':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
	case 'p':
	    if (xmlStrEqual(node->name, BAD_CAST "STR"))
		return(1);
	    return(0);
    }
    return(0);
}