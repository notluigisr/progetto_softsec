EXPORTED void mailbox_get_usage(struct mailbox *mailbox,
                        quota_t usage[QUOTA_NUMRESOURCES])
{
    int res;

    for (res = 0; res < QUOTA_NUMRESOURCES; res++) {
        usage[res] = 0;
    }

    if (!(mailbox->i.options & OPT_MAILBOX_DELETED)) {
        usage[QUOTA_STORAGE] = mailbox->i.quota_mailbox_used;
        usage[QUOTA_MESSAGE] = mailbox->i.exists;
        usage[QUOTA_ANNOTSTORAGE] = mailbox->i.quota_annot_used;
        usage[QUOTA_NUMFOLDERS] = 1;
    }
    
}