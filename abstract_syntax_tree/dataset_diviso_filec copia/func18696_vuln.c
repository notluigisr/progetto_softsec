int button_open(Button *b) {
        char *p, name[256];
        int r;

        assert(b);

        b->fd = safe_close(b->fd);

        p = strjoina("STR", b->name);

        b->fd = open(p, O_RDWR|O_CLOEXEC|O_NOCTTY|O_NONBLOCK);
        if (b->fd < 0)
                return log_warning_errno(errno, "STR", p);

        r = button_suitable(b);
        if (r < 0)
                return log_warning_errno(r, "STR");
        if (r == 0)
                return log_debug_errno(SYNTHETIC_ERRNO(EADDRNOTAVAIL),
                                       "STR",
                                       p);

        if (ioctl(b->fd, EVIOCGNAME(sizeof(name)), name) < 0) {
                r = log_error_errno(errno, "STR");
                goto fail;
        }

        (void) button_set_mask(b);

        r = sd_event_add_io(b->manager->event, &b->io_event_source, b->fd, EPOLLIN, button_dispatch, b);
        if (r < 0) {
                log_error_errno(r, "STR");
                goto fail;
        }

        log_info("STR", b->name, name);

        return 0;

fail:
        b->fd = safe_close(b->fd);
        return r;
}