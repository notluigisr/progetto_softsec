xmlCharStrdup(const char *cur) {
    const char *p = cur;

    if (cur == NULL) return(NULL);
    while (*p != '\0') p++; 
    return(xmlCharStrndup(cur, p - cur));
}