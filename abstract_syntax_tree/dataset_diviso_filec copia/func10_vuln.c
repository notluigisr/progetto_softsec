add_mibdir(const char *dirname)
{
    FILE           *ip;
    const char     *oldFile = File;
    char          **filenames;
    int             count = 0;
    int             filename_count, i;
#if !(defined(WIN32) || defined(cygwin))
    char           *token;
    char space;
    char newline;
    struct stat     dir_stat, idx_stat;
    char            tmpstr[300];
    char            tmpstr1[300];
#endif

    DEBUGMSGTL(("STR", dirname));
#if !(defined(WIN32) || defined(cygwin))
    token = netsnmp_mibindex_lookup( dirname );
    if (token && stat(token, &idx_stat) == 0 && stat(dirname, &dir_stat) == 0) {
        if (dir_stat.st_mtime < idx_stat.st_mtime) {
            DEBUGMSGTL(("STR"));
            if ((ip = fopen(token, "STR")) != NULL) {
                fgets(tmpstr, sizeof(tmpstr), ip); 
                while (fscanf(ip, "STR", token, &space, tmpstr,
		    &newline) == 4) {

		    
		    if (space != ' ' || newline != '\n') {
			snmp_log(LOG_ERR,
			    "STR" \
			    "STR", dirname,
			    "STR", count);
			    break;
		    }
		   
		    snprintf(tmpstr1, sizeof(tmpstr1), "STR", dirname, tmpstr);
                    tmpstr1[ sizeof(tmpstr1)-1 ] = 0;
                    new_module(token, tmpstr1);
                    count++;
                }
                fclose(ip);
                return count;
            } else
                DEBUGMSGTL(("STR"));
        } else
            DEBUGMSGTL(("STR"));
    } else
        DEBUGMSGTL(("STR"));
#endif

    filename_count = scan_directory(&filenames, dirname);

    if (filename_count >= 0) {
        ip = netsnmp_mibindex_new(dirname);
        for (i = 0; i < filename_count; i++) {
            if (add_mibfile(filenames[i], strrchr(filenames[i], '/'), ip) == 0)
                count++;
	    free(filenames[i]);
        }
        File = oldFile;
        if (ip)
            fclose(ip);
        free(filenames);
        return (count);
    }
    else
        DEBUGMSGTL(("STR", dirname));

    return (-1);
}