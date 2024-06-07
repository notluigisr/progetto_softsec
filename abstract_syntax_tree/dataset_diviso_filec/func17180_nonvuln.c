HIDDEN int mailbox_changequotaroot(struct mailbox *mailbox,
                                   const char *root, int silent)
{
    int r = 0;
    int res;
    quota_t quota_usage[QUOTA_NUMRESOURCES];

    mailbox_get_usage(mailbox, quota_usage);

    if (mailbox->h.quotaroot) {
        quota_t quota_diff[QUOTA_NUMRESOURCES];

        if (root) {
            size_t len = strlen(root);
            if (strlen(mailbox->h.quotaroot) >= len && !strncmp(mailbox->h.quotaroot, root, len) &&
                (mailbox->h.quotaroot[len] == '\0' || mailbox->h.quotaroot[len] == '.')) {
                    
                    goto done;
            }
        }

        
        for (res = 0; res < QUOTA_NUMRESOURCES ; res++) {
            quota_diff[res] = -quota_usage[res];
        }
        r = quota_update_useds(mailbox->h.quotaroot, quota_diff,
                               mailbox_name(mailbox), silent);
    }

    
    mailbox_set_quotaroot(mailbox, root);

    if (root) {
        
        r = quota_update_useds(root, quota_usage, mailbox_name(mailbox), silent);
    }

  done:
    return r;
}