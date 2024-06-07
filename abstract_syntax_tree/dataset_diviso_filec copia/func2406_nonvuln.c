xmlNewDocNode(xmlDocPtr doc, xmlNsPtr ns,
              const xmlChar *name, const xmlChar *content) {
    xmlNodePtr cur;

    if ((doc != NULL) && (doc->dict != NULL))
        cur = xmlNewNodeEatName(ns, (xmlChar *)
	                        xmlDictLookup(doc->dict, name, -1));
    else
	cur = xmlNewNode(ns, name);
    if (cur != NULL) {
        cur->doc = doc;
	if (content != NULL) {
	    cur->children = xmlStringGetNodeList(doc, content);
	    UPDATE_LAST_CHILD_AND_PARENT(cur)
	}
    }

    return(cur);
}