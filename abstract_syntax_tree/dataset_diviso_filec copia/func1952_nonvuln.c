int journal_remote_add_source(RemoteServer *s, int fd, char* name, bool own_name) {
        RemoteSource *source = NULL;
        int r;

        

        assert(s);
        assert(fd >= 0);
        assert(name);

        if (!own_name) {
                name = strdup(name);
                if (!name)
                        return log_oom();
        }

        r = get_source_for_fd(s, fd, name, &source);
        if (r < 0) {
                log_error_errno(r, "STR",
                                fd, name);
                free(name);
                return r;
        }

        r = sd_event_add_io(s->events, &source->event,
                            fd, EPOLLIN|EPOLLRDHUP|EPOLLPRI,
                            dispatch_raw_source_event, source);
        if (r == 0) {
                
                r = sd_event_add_defer(s->events, &source->buffer_event,
                                       dispatch_raw_source_until_block, source);
                if (r == 0)
                        sd_event_source_set_enabled(source->buffer_event, SD_EVENT_OFF);
        } else if (r == -EPERM) {
                log_debug("STR", fd, name);
                r = sd_event_add_defer(s->events, &source->event,
                                       dispatch_blocking_source_event, source);
                if (r == 0)
                        sd_event_source_set_enabled(source->event, SD_EVENT_ON);
        }
        if (r < 0) {
                log_error_errno(r, "STR",
                                fd);
                goto error;
        }

        r = sd_event_source_set_description(source->event, name);
        if (r < 0) {
                log_error_errno(r, "STR", fd);
                goto error;
        }

        return 1; 

 error:
        remove_source(s, fd);
        return r;
}