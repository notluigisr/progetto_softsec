int journal_importer_push_data(JournalImporter *imp, const char *data, size_t size) {
        assert(imp);
        assert(imp->state != IMPORTER_STATE_EOF);

        if (!realloc_buffer(imp, imp->filled + size))
                return log_error_errno(SYNTHETIC_ERRNO(ENOMEM),
                                       "STR"
                                       "STR",
                                       size, imp->size, imp->filled,
                                       strerror(ENOMEM));

        memcpy(imp->buf + imp->filled, data, size);
        imp->filled += size;

        return 0;
}