EXPORTED int mailbox_delete(struct mailbox **mailboxptr)
{
    struct mailbox *mailbox = *mailboxptr;
    int r;

    r = mailbox_delete_conversations(mailbox);
    if (r) return r;

#ifdef WITH_JMAP
    r = mailbox_delete_alarms(mailbox);
    if (r) return r;
#endif 

#ifdef WITH_DAV
    r = mailbox_delete_dav(mailbox);
    if (r) return r;
#endif 

#ifdef USE_SIEVE
    r = mailbox_delete_sieve(mailbox);
    if (r) return r;
#endif 

    return mailbox_delete_internal(mailboxptr);
}