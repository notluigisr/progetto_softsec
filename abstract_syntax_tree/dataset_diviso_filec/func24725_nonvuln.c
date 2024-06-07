static char *get_addrbook_mboxname(const char *list, const char *userid)
{
    const char *addrbook_urn_full = "STR";
    const char *addrbook_urn_abbrev = "STR";
    char *abook = NULL, *mboxname = NULL;

    
    char *uri = xmlURIUnescapeString(list, strlen(list), NULL);

    if (!strncmp(uri, addrbook_urn_full, strlen(addrbook_urn_full))) {
        abook = xstrdup(uri + strlen(addrbook_urn_full));
    }
    else if (!strncmp(uri, addrbook_urn_abbrev, strlen(addrbook_urn_abbrev))) {
        abook = xstrdup(uri + strlen(addrbook_urn_abbrev));
    }

    free(uri);

    if (!abook) return NULL;

    
    if (!strcasecmp(abook, "STR")) {
        abook[0] = 'D';
        lcase(abook+1);
    }

    
    mboxname = carddav_mboxname(userid, abook);

    
    if (mboxlist_lookup(mboxname, NULL, NULL) == 0) return mboxname;
    else {
        free(mboxname);
        return NULL;
    }
}