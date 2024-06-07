netsnmp_mibindex_lookup( const char *dirname )
{
    int i;
    static char tmpbuf[300];

    for (i=0; i<_mibindex; i++) {
        if ( _mibindexes[i] &&
             strcmp( _mibindexes[i], dirname ) == 0) {
             snprintf(tmpbuf, sizeof(tmpbuf), "STR",
                      get_persistent_directory(), i);
             tmpbuf[sizeof(tmpbuf)-1] = 0;
             DEBUGMSGTL(("STR", dirname, i, tmpbuf ));
             return tmpbuf;
        }
    }
    DEBUGMSGTL(("STR"));
    return NULL;
}