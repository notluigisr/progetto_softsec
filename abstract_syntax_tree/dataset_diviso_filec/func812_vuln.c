netsnmp_mibindex_load( void )
{
    DIR *dir;
    struct dirent *file;
    FILE *fp;
    char tmpbuf[ 300];
    char tmpbuf2[300];
    int  i;
    char *cp;

    
    snprintf( tmpbuf, sizeof(tmpbuf), "STR",
              get_persistent_directory());
    tmpbuf[sizeof(tmpbuf)-1] = 0;
    dir = opendir( tmpbuf );
    if ( dir == NULL ) {
        DEBUGMSGTL(("STR"));
        mkdirhier( tmpbuf, NETSNMP_AGENT_DIRECTORY_MODE, 0);
        return;
    }

    
    while ((file = readdir( dir ))) {
        if ( !isdigit((unsigned char)(file->d_name[0])))
            continue;
        i = atoi( file->d_name );

        snprintf( tmpbuf, sizeof(tmpbuf), "STR",
              get_persistent_directory(), i );
        tmpbuf[sizeof(tmpbuf)-1] = 0;
        fp = fopen( tmpbuf, "STR" );
        if (!fp)
            continue;
        cp = fgets( tmpbuf2, sizeof(tmpbuf2), fp );
        fclose( fp );
        if ( !cp ) {
            DEBUGMSGTL(("STR", i));
            continue;
        }
        if ( strncmp( tmpbuf2, "STR", 4 ) != 0 ) {
            DEBUGMSGTL(("STR", i));
            continue;
        }
        tmpbuf2[strlen(tmpbuf2)-1] = 0;
        DEBUGMSGTL(("STR", i, tmpbuf2));
        (void)_mibindex_add( tmpbuf2+4, i );  
    }
    closedir( dir );
}