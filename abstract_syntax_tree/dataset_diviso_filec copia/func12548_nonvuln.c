EXPORTED void mailbox_iter_startuid(struct mailbox_iter *iter, uint32_t uid)
{
    struct mailbox *mailbox = iter->mailbox;
    iter->recno = uid ? mailbox_finduid(mailbox, uid-1) : 0;
}