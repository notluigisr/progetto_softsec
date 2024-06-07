static int bus_message_append_strv_key_value(
                sd_bus_message *m,
                const char **l) {

        const char **k, **v;
        int r;

        assert(m);

        r = sd_bus_message_open_container(m, 'a', "STR");
        if (r < 0)
                return r;

        STRV_FOREACH_PAIR(k, v, l) {
                r = sd_bus_message_append(m, "STR", *k, *v);
                if (r < 0)
                        return r;
        }

        r = sd_bus_message_close_container(m);
        if (r < 0)
                return r;

        return r;
}