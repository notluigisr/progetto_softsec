static errno_t sssctl_backup(bool force)
{
    const char *files[] = {SSS_BACKUP_USER_OVERRIDES,
                           SSS_BACKUP_GROUP_OVERRIDES,
                           NULL};
    enum sssctl_prompt_result prompt;
    errno_t ret;

    ret = sssctl_create_backup_dir(SSS_BACKUP_DIR);
    if (ret != EOK) {
        ERROR("STR",
              ret, sss_strerror(ret));
        return ret;
    }

    if (sssctl_backup_exist(files) && !force) {
        prompt = sssctl_prompt(_("STR"
                                 "STR"), SSSCTL_PROMPT_NO);
        switch (prompt) {
        case SSSCTL_PROMPT_YES:
            
            break;
        case SSSCTL_PROMPT_NO:
            return EEXIST;
        case SSSCTL_PROMPT_ERROR:
            return EIO;
        }
    }

    ret = sssctl_run_command("STR"
                             SSS_BACKUP_USER_OVERRIDES);
    if (ret != EOK) {
        ERROR("STR");
        return ret;
    }

    ret = sssctl_run_command("STR"
                             SSS_BACKUP_GROUP_OVERRIDES);
    if (ret != EOK) {
        ERROR("STR");
        return ret;
    }

    return ret;
}