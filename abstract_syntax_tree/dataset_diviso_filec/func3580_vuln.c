static void automount_enter_runnning(Automount *a) {
        _cleanup_(sd_bus_error_free) sd_bus_error error = SD_BUS_ERROR_NULL;
        struct stat st;
        int r;

        assert(a);

        
        if (UNIT(a)->load_state != UNIT_LOADED) {
                log_unit_error(UNIT(a), "STR");
                goto fail;
        }

        
        if (unit_stop_pending(UNIT(a))) {
                log_unit_debug(UNIT(a), "STR");
                automount_send_ready(a, a->tokens, -EHOSTDOWN);
                automount_send_ready(a, a->expire_tokens, -EHOSTDOWN);
                return;
        }

        mkdir_p_label(a->where, a->directory_mode);

        
        if (lstat(a->where, &st) < 0) {
                log_unit_warning_errno(UNIT(a), errno, "STR");
                goto fail;
        }

        if (!S_ISDIR(st.st_mode) || st.st_dev != a->dev_id)
                log_unit_info(UNIT(a), "STR");
        else {
                Unit *trigger;

                trigger = UNIT_TRIGGER(UNIT(a));
                if (!trigger) {
                        log_unit_error(UNIT(a), "STR");
                        goto fail;
                }

                r = manager_add_job(UNIT(a)->manager, JOB_START, trigger, JOB_REPLACE, &error, NULL);
                if (r < 0) {
                        log_unit_warning(UNIT(a), "STR", bus_error_message(&error, r));
                        goto fail;
                }
        }

        automount_set_state(a, AUTOMOUNT_RUNNING);
        return;

fail:
        automount_enter_dead(a, AUTOMOUNT_FAILURE_RESOURCES);
}