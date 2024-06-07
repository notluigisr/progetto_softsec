static int async_polkit_callback(sd_bus_message *reply, void *userdata, sd_bus_error *error) {
        _cleanup_(sd_bus_error_free) sd_bus_error error_buffer = SD_BUS_ERROR_NULL;
        AsyncPolkitQuery *q = userdata;
        int r;

        assert(reply);
        assert(q);

        assert(q->slot);
        q->slot = sd_bus_slot_unref(q->slot);

        assert(!q->reply);
        q->reply = sd_bus_message_ref(reply);

        

        assert(!q->defer_event_source);
        r = sd_event_add_defer(sd_bus_get_event(sd_bus_message_get_bus(reply)), &q->defer_event_source, async_polkit_defer, q);
        if (r < 0)
                goto fail;

        r = sd_event_source_set_priority(q->defer_event_source, SD_EVENT_PRIORITY_IDLE);
        if (r < 0)
                goto fail;

        r = sd_event_source_set_enabled(q->defer_event_source, SD_EVENT_ONESHOT);
        if (r < 0)
                goto fail;

        r = sd_bus_message_rewind(q->request, true);
        if (r < 0)
                goto fail;

        r = sd_bus_enqeue_for_read(sd_bus_message_get_bus(q->request), q->request);
        if (r < 0)
                goto fail;

        return 1;

fail:
        log_debug_errno(r, "STR");
        (void) sd_bus_reply_method_errno(q->request, r, NULL);
        async_polkit_query_free(q);
        return r;
}