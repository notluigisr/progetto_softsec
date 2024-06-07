static void process_watch_command(conn *c, token_t *tokens, const size_t ntokens) {
    uint16_t f = 0;
    int x;
    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);
    if (ntokens > 2) {
        for (x = COMMAND_TOKEN + 1; x < ntokens - 1; x++) {
            if ((strcmp(tokens[x].value, "STR") == 0)) {
                f |= LOG_RAWCMDS;
            } else if ((strcmp(tokens[x].value, "STR") == 0)) {
                f |= LOG_EVICTIONS;
            } else if ((strcmp(tokens[x].value, "STR") == 0)) {
                f |= LOG_FETCHERS;
            } else if ((strcmp(tokens[x].value, "STR") == 0)) {
                f |= LOG_MUTATIONS;
            } else if ((strcmp(tokens[x].value, "STR") == 0)) {
                f |= LOG_SYSEVENTS;
            } else {
                out_string(c, "STR");
                return;
            }
        }
    } else {
        f |= LOG_FETCHERS;
    }

    switch(logger_add_watcher(c, c->sfd, f)) {
        case LOGGER_ADD_WATCHER_TOO_MANY:
            out_string(c, "STR");
            break;
        case LOGGER_ADD_WATCHER_FAILED:
            out_string(c, "STR");
            break;
        case LOGGER_ADD_WATCHER_OK:
            conn_set_state(c, conn_watch);
            event_del(&c->event);
            break;
    }
}