_public_ sd_bus* sd_bus_flush_close_unref(sd_bus *bus) {
        if (!bus)
                return NULL;

        
        bus_kill_exec(bus);
        sd_bus_flush(bus);

        return sd_bus_close_unref(bus);
}