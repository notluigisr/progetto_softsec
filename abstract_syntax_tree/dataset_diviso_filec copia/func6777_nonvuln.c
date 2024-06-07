xmlStrcat(xmlChar *cur, const xmlChar *add) {
    const xmlChar *p = add;

    if (add == NULL) return(cur);
    if (cur == NULL)
        return(xmlStrdup(add));

    while (*p != 0) p++; 
    return(xmlStrncat(cur, add, p - add));
}