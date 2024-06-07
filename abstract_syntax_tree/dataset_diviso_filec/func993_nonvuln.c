int bus_deserialize_and_dump_unit_file_changes(sd_bus_message *m, bool quiet, UnitFileChange **changes, size_t *n_changes) {
        const char *type, *path, *source;
        int r;

        
        assert(changes);
        assert(n_changes);

        r = sd_bus_message_enter_container(m, SD_BUS_TYPE_ARRAY, "STR");
        if (r < 0)
                return bus_log_parse_error(r);

        while ((r = sd_bus_message_read(m, "STR", &type, &path, &source)) > 0) {
                
                UnitFileChangeType ch = unit_file_change_type_from_string(type);

                if (ch < 0) {
                        log_notice("STR", type, path);
                        continue;
                }

                r = unit_file_changes_add(changes, n_changes, ch, path, source);
                if (r < 0)
                        return r;
        }
        if (r < 0)
                return bus_log_parse_error(r);

        r = sd_bus_message_exit_container(m);
        if (r < 0)
                return bus_log_parse_error(r);

        unit_file_dump_changes(0, NULL, *changes, *n_changes, quiet);
        return 0;
}