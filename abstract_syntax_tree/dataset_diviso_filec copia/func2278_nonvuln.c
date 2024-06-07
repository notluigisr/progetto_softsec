static struct mappedfile *mailbox_cachefile(struct mailbox *mailbox,
                                            const struct index_record *record)
{
    const char *fname;

    if (record->internal_flags & FLAG_INTERNAL_ARCHIVED)
        fname = mailbox_meta_fname(mailbox, META_ARCHIVECACHE);
    else
        fname = mailbox_meta_fname(mailbox, META_CACHE);

    return cache_getfile(&mailbox->caches, fname, mailbox->is_readonly, mailbox->i.generation_no);
}