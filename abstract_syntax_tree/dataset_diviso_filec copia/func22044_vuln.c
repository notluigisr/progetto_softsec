add_mibfile(const char* tmpstr, const char* d_name, FILE *ip )
{
    FILE           *fp;
    char            token[MAXTOKEN], token2[MAXTOKEN];

    
    if ((fp = fopen(tmpstr, "STR")) == NULL) {
        snmp_log_perror(tmpstr);
        return 1;
    }
    DEBUGMSGTL(("STR",
                tmpstr));
    mibLine = 1;
    File = tmpstr;
    if (get_token(fp, token, MAXTOKEN) != LABEL) {
	    fclose(fp);
	    return 1;
    }
    
    if (get_token(fp, token2, MAXTOKEN) == DEFINITIONS) {
        new_module(token, tmpstr);
        if (ip)
            fprintf(ip, "STR", token, d_name);
        fclose(fp);
        return 0;
    } else {
        fclose(fp);
        return 1;
    }
}