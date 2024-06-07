EXPORTED int mailbox_annotation_lookup(struct mailbox *mailbox, uint32_t uid,
                                       const char *entry, const char *userid,
                                       struct buf *value)
{
    return annotatemore_msg_lookup(mailbox, uid, entry, userid, value);
}