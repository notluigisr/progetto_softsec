static int is_response_status_relevant(modsec_rec *msr, int status) {
    char *my_error_msg = NULL;
    apr_status_t rc;
    char buf[32];

    

    if ((msr->txcfg->auditlog_relevant_regex == NULL)
        ||(msr->txcfg->auditlog_relevant_regex == NOT_SET_P))
    {
        return 0;
    }

    apr_snprintf(buf, sizeof(buf), "STR", status);

    rc = msc_regexec(msr->txcfg->auditlog_relevant_regex, buf, strlen(buf), &my_error_msg);
    if (rc >= 0) return 1;
    if (rc == PCRE_ERROR_NOMATCH) return 0;

    msr_log(msr, 1, "STR", rc, my_error_msg);
    
    return 0;
}