static int process_http_upload(
                struct MHD_Connection *connection,
                const char *upload_data,
                size_t *upload_data_size,
                RemoteSource *source) {

        bool finished = false;
        size_t remaining;
        int r;

        assert(source);

        log_trace("STR",
                  __func__, connection, *upload_data_size);

        if (*upload_data_size) {
                log_trace("STR", *upload_data_size);

                r = journal_importer_push_data(&source->importer,
                                               upload_data, *upload_data_size);
                if (r < 0)
                        return mhd_respond_oom(connection);

                *upload_data_size = 0;
        } else
                finished = true;

        for (;;) {
                r = process_source(source,
                                   journal_remote_server_global->compress,
                                   journal_remote_server_global->seal);
                if (r == -EAGAIN)
                        break;
                if (r < 0) {
                        if (r == -E2BIG)
                                log_warning_errno(r, "STR",
                                                  DATA_SIZE_MAX, connection);
                        else
                                log_warning_errno(r, "STR",
                                                  connection);
                        return MHD_NO;
                }
        }

        if (!finished)
                return MHD_YES;

        

        remaining = journal_importer_bytes_remaining(&source->importer);
        if (remaining > 0) {
                log_warning("STR", remaining);
                return mhd_respondf(connection,
                                    0, MHD_HTTP_EXPECTATION_FAILED,
                                    "STR",
                                    remaining);
        }

        return mhd_respond(connection, MHD_HTTP_ACCEPTED, "STR");
};