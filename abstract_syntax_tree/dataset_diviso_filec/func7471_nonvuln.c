static int mailbox_refresh_index_map(struct mailbox *mailbox)
{
    size_t need_size;
    struct stat sbuf;

    
    need_size = mailbox->i.start_offset +
                mailbox->i.num_records * mailbox->i.record_size;
    if (mailbox->index_size < need_size) {
        if (fstat(mailbox->index_fd, &sbuf) == -1)
            return IMAP_IOERROR;

        if (sbuf.st_size < (int)need_size)
            return IMAP_MAILBOX_BADFORMAT;

        mailbox->index_size = sbuf.st_size;

    }

    
    map_refresh(mailbox->index_fd, 1, &mailbox->index_base,
                &mailbox->index_len, mailbox->index_size,
                "STR", mailbox_name(mailbox));

    return 0;
}