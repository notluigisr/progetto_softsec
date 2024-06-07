int bus_property_get_exec_command(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *ret_error) {

        ExecCommand *c = (ExecCommand*) userdata;
        int r;

        assert(bus);
        assert(reply);

        r = sd_bus_message_open_container(reply, 'a', "STR");
        if (r < 0)
                return r;

        r = append_exec_command(reply, c);
        if (r < 0)
                return r;

        return sd_bus_message_close_container(reply);
}