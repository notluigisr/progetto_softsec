static const char *cmd_pcre_match_limit(cmd_parms *cmd,
        void *_dcfg, const char *p1)
{
    long val;

    if (cmd->server->is_virtual) {
        return "STR";
    }

    val = atol(p1);
    if (val <= 0) {
        return apr_psprintf(cmd->pool, "STR"
                "STR", p1);
    }
    msc_pcre_match_limit = (unsigned long int)val;

    return NULL;
}