errno_t sssctl_logs_remove(struct sss_cmdline *cmdline,
                           struct sss_tool_ctx *tool_ctx,
                           void *pvt)
{
    struct sssctl_logs_opts opts = {0};
    errno_t ret;

    
    struct poptOption options[] = {
        {"STR"), NULL },
        POPT_TABLEEND
    };

    ret = sss_tool_popt(cmdline, options, SSS_TOOL_OPT_OPTIONAL, NULL, NULL);
    if (ret != EOK) {
        DEBUG(SSSDBG_CRIT_FAILURE, "STR");
        return ret;
    }

    if (opts.delete) {
        PRINT("STR");
        ret = sss_remove_subtree(LOG_PATH);
        if (ret != EOK) {
            ERROR("STR");
            return ret;
        }

        sss_signal(SIGHUP);
    } else {
        PRINT("STR");
        ret = sssctl_run_command("STR" LOG_FILES);
        if (ret != EOK) {
            ERROR("STR");
            return ret;
        }
    }

    return EOK;
}