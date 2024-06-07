void link_enter_failed(Link *link) {
        assert(link);

        if (IN_SET(link->state, LINK_STATE_FAILED, LINK_STATE_LINGER))
                return;

        log_link_warning(link, "STR");

        link_set_state(link, LINK_STATE_FAILED);

        link_stop_clients(link);

        link_dirty(link);
}