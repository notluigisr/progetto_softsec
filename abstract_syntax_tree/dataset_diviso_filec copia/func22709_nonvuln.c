xmlFreeDtd(xmlDtdPtr cur) {
    xmlDictPtr dict = NULL;

    if (cur == NULL) {
	return;
    }
    if (cur->doc != NULL) dict = cur->doc->dict;

    if ((__xmlRegisterCallbacks) && (xmlDeregisterNodeDefaultValue))
	xmlDeregisterNodeDefaultValue((xmlNodePtr)cur);

    if (cur->children != NULL) {
	xmlNodePtr next, c = cur->children;

	
        while (c != NULL) {
	    next = c->next;
	    if ((c->type != XML_NOTATION_NODE) &&
	        (c->type != XML_ELEMENT_DECL) &&
		(c->type != XML_ATTRIBUTE_DECL) &&
		(c->type != XML_ENTITY_DECL)) {
		xmlUnlinkNode(c);
		xmlFreeNode(c);
	    }
	    c = next;
	}
    }
    DICT_FREE(cur->name)
    DICT_FREE(cur->SystemID)
    DICT_FREE(cur->ExternalID)
    
    if (cur->notations != NULL)
        xmlFreeNotationTable((xmlNotationTablePtr) cur->notations);

    if (cur->elements != NULL)
        xmlFreeElementTable((xmlElementTablePtr) cur->elements);
    if (cur->attributes != NULL)
        xmlFreeAttributeTable((xmlAttributeTablePtr) cur->attributes);
    if (cur->entities != NULL)
        xmlFreeEntitiesTable((xmlEntitiesTablePtr) cur->entities);
    if (cur->pentities != NULL)
        xmlFreeEntitiesTable((xmlEntitiesTablePtr) cur->pentities);

    xmlFree(cur);
}