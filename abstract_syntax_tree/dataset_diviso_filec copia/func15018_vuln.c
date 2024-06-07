errno_t sssctl_run_command(const char *command)
{
    int ret;

    DEBUG(SSSDBG_TRACE_FUNC, "STR", command);

    ret = system(command);
    if (ret == -1) {
        DEBUG(SSSDBG_CRIT_FAILURE, "STR", command);
        ERROR("STR");
        return EFAULT;
    } else if (WEXITSTATUS(ret) != 0) {
        DEBUG(SSSDBG_CRIT_FAILURE, "STR",
              command, WEXITSTATUS(ret));
        ERROR("STR");
        return EIO;
    }

    return EOK;
}