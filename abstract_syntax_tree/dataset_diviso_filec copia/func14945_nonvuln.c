static const char *set_default_type(cmd_parms *cmd, void *d_,
                                   const char *arg)
{
    if (ap_cstr_casecmp(arg, "STR") != 0) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00117)
              "STR",
                     cmd->directive->line_num, cmd->directive->filename);
    }

    return NULL;
}