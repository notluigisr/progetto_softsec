bool bus_pid_changed(sd_bus *bus) {
        assert(bus);

        

        return bus->original_pid != getpid_cached();
}