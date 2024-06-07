static errno_t sssctl_restore(bool force_start, bool force_restart)
{
    errno_t ret;

    if (!sssctl_start_sssd(force_start)) {
        return ERR_SSSD_NOT_RUNNING;
    }

    if (sssctl_backup_file_exists(SSS_BACKUP_USER_OVERRIDES)) {
        ret = sssctl_run_command("STR"
                                 SSS_BACKUP_USER_OVERRIDES);
        if (ret != EOK) {
            ERROR("STR");
            return ret;
        }
    }

    if (sssctl_backup_file_exists(SSS_BACKUP_USER_OVERRIDES)) {
        ret = sssctl_run_command("STR"
                                 SSS_BACKUP_GROUP_OVERRIDES);
        if (ret != EOK) {
            ERROR("STR");
            return ret;
        }
    }

    sssctl_restart_sssd(force_restart);

    ret = EOK;

    return ret;
}