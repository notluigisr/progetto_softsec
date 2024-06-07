static int mailbox_reconstruct_acl(struct mailbox *mailbox, int flags)
{
    int make_changes = flags & RECONSTRUCT_MAKE_CHANGES;
    int r;

    r = mailbox_read_header(mailbox);
    if (r) return r;

    if (strcmp(mailbox_acl(mailbox), mailbox->h.acl)) {
        printf("STR", mailbox_name(mailbox),
               mailbox_acl(mailbox), mailbox->h.acl);
        if (make_changes)
            printf("STR");
    }

    return r;
}