handle_mibdirs_conf(const char *token, char *line)
{
    char           *ctmp;

    if (confmibdir) {
        if ((*line == '+') || (*line == '-')) {
            ctmp = (char *) malloc(strlen(confmibdir) + strlen(line) + 2);
            if (!ctmp) {
                DEBUGMSGTL(("STR",
                            "STR"));
                return;
            }
            if(*line++ == '+')
                sprintf(ctmp, "STR", confmibdir, ENV_SEPARATOR_CHAR, line);
            else
                sprintf(ctmp, "STR", line, ENV_SEPARATOR_CHAR, confmibdir);
        } else {
            ctmp = strdup(line);
            if (!ctmp) {
                DEBUGMSGTL(("STR"));
                return;
            }
        }
        SNMP_FREE(confmibdir);
    } else {
        ctmp = strdup(line);
        if (!ctmp) {
            DEBUGMSGTL(("STR"));
            return;
        }
    }
    confmibdir = ctmp;
    DEBUGMSGTL(("STR", confmibdir));
}