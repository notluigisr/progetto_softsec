xmlDictCreateSub(xmlDictPtr sub) {
    xmlDictPtr dict = xmlDictCreate();

    if ((dict != NULL) && (sub != NULL)) {
#ifdef DICT_DEBUG_PATTERNS
        fprintf(stderr, "STR");
#endif
        dict->subdict = sub;
	xmlDictReference(dict->subdict);
    }
    return(dict);
}