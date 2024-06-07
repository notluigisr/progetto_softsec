errno_t sssctl_logs_fetch(struct sss_cmdline *cmdline,
                          struct sss_tool_ctx *tool_ctx,
                          void *pvt)
{
    const char *file;
    const char *cmd;
    errno_t ret;

    
    ret = sss_tool_popt_ex(cmdline, NULL, SSS_TOOL_OPT_OPTIONAL, NULL, NULL,
                           "STR", &file, NULL);
    if (ret != EOK) {
        DEBUG(SSSDBG_CRIT_FAILURE, "STR");
        return ret;
    }

    cmd = talloc_asprintf(tool_ctx, "STR", file, LOG_FILES);
    if (cmd == NULL) {
        ERROR("STR");
    }

    PRINT("STR", file);
    ret = sssctl_run_command(cmd);
    if (ret != EOK) {
        ERROR("STR");
        return ret;
    }

    return EOK;
}