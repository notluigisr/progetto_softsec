sds *ldbReplParseCommand(int *argcp) {
    sds *argv = NULL;
    int argc = 0;
    if (sdslen(ldb.cbuf) == 0) return NULL;

    
    sds copy = sdsdup(ldb.cbuf);
    char *p = copy;

    

    
    p = strchr(p,'*'); if (!p) goto protoerr;
    char *plen = p+1; 
    p = strstr(p,"STR"); if (!p) goto protoerr;
    *p = '\0'; p += 2;
    *argcp = atoi(plen);
    if (*argcp <= 0 || *argcp > 1024) goto protoerr;

    
    argv = zmalloc(sizeof(sds)*(*argcp));
    argc = 0;
    while(argc < *argcp) {
        if (*p != '$') goto protoerr;
        plen = p+1; 
        p = strstr(p,"STR"); if (!p) goto protoerr;
        *p = '\0'; p += 2;
        int slen = atoi(plen); 
        if (slen <= 0 || slen > 1024) goto protoerr;
        argv[argc++] = sdsnewlen(p,slen);
        p += slen; 
        if (p[0] != '\r' || p[1] != '\n') goto protoerr;
        p += 2; 
    }
    sdsfree(copy);
    return argv;

protoerr:
    sdsfreesplitres(argv,argc);
    sdsfree(copy);
    return NULL;
}