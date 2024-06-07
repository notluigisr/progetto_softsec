xmlXPathNodeSetAddUnique(xmlNodeSetPtr cur, xmlNodePtr val) {
    if ((cur == NULL) || (val == NULL)) return;

#if 0
    if ((val->type == XML_ELEMENT_NODE) && (val->name[0] == ' '))
	return;	
#endif

    
    
    if (cur->nodeMax == 0) {
        cur->nodeTab = (xmlNodePtr *) xmlMalloc(XML_NODESET_DEFAULT *
					     sizeof(xmlNodePtr));
	if (cur->nodeTab == NULL) {
	    xmlXPathErrMemory(NULL, "STR");
	    return;
	}
	memset(cur->nodeTab, 0 ,
	       XML_NODESET_DEFAULT * (size_t) sizeof(xmlNodePtr));
        cur->nodeMax = XML_NODESET_DEFAULT;
    } else if (cur->nodeNr == cur->nodeMax) {
        xmlNodePtr *temp;

        cur->nodeMax *= 2;
	temp = (xmlNodePtr *) xmlRealloc(cur->nodeTab, cur->nodeMax *
				      sizeof(xmlNodePtr));
	if (temp == NULL) {
	    xmlXPathErrMemory(NULL, "STR");
	    return;
	}
	cur->nodeTab = temp;
    }
    if (val->type == XML_NAMESPACE_DECL) {
	xmlNsPtr ns = (xmlNsPtr) val;

	cur->nodeTab[cur->nodeNr++] =
	    xmlXPathNodeSetDupNs((xmlNodePtr) ns->next, ns);
    } else
	cur->nodeTab[cur->nodeNr++] = val;
}