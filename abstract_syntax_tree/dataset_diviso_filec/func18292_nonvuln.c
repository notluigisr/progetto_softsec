_public_ sd_event* sd_bus_get_event(sd_bus *bus) {
        assert_return(bus, NULL);

        return bus->event;
}