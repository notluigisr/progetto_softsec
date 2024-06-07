netsnmp_mibindex_new( const char *dirname )
{
    FILE *fp;
    char  tmpbuf[300];
    char *cp;
    int   i;

    cp = netsnmp_mibindex_lookup( dirname );
    if (!cp) {
        i  = _mibindex_add( dirname, -1 );
        snprintf( tmpbuf, sizeof(tmpbuf), "STR",
                  get_persistent_directory(), i );
        tmpbuf[sizeof(tmpbuf)-1] = 0;
        cp = tmpbuf;
    }
    DEBUGMSGTL(("STR", dirname, cp ));
    fp = fopen( cp, "STR" );
    if (fp)
        fprintf( fp, "STR", dirname );
    return fp;
}