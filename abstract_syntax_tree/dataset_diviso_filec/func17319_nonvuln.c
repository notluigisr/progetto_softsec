xmlDelEncodingAlias(const char *alias) {
    int i;

    if (alias == NULL)
	return(-1);

    if (xmlCharEncodingAliases == NULL)
	return(-1);
    
    for (i = 0;i < xmlCharEncodingAliasesNb;i++) {
	if (!strcmp(xmlCharEncodingAliases[i].alias, alias)) {
	    xmlFree((char *) xmlCharEncodingAliases[i].name);
	    xmlFree((char *) xmlCharEncodingAliases[i].alias);
	    xmlCharEncodingAliasesNb--;
	    memmove(&xmlCharEncodingAliases[i], &xmlCharEncodingAliases[i + 1],
		    sizeof(xmlCharEncodingAlias) * (xmlCharEncodingAliasesNb - i));
	    return(0);
	}
    }
    return(-1);
}