choose_windows(s)
const char *s;
{
    register int i;

    for (i = 0; winchoices[i].procs; i++) {
        if ('+' == winchoices[i].procs->name[0])
            continue;
        if ('-' == winchoices[i].procs->name[0])
            continue;
        if (!strcmpi(s, winchoices[i].procs->name)) {
            windowprocs = *winchoices[i].procs;

            if (last_winchoice && last_winchoice->ini_routine)
                (*last_winchoice->ini_routine)(WININIT_UNDO);
            if (winchoices[i].ini_routine)
                (*winchoices[i].ini_routine)(WININIT);
            last_winchoice = &winchoices[i];
            return;
        }
    }

    if (!windowprocs.win_raw_print)
        windowprocs.win_raw_print = def_raw_print;
    if (!windowprocs.win_wait_synch)
        
        windowprocs.win_wait_synch = def_wait_synch;

    if (!winchoices[0].procs) {
        raw_printf("STR");
        nh_terminate(EXIT_FAILURE);
    }
    if (!winchoices[1].procs) {
        config_error_add(
                     "STR",
                         s, winchoices[0].procs->name);
    } else {
        char buf[BUFSZ];
        boolean first = TRUE;

        buf[0] = '\0';
        for (i = 0; winchoices[i].procs; i++) {
            if ('+' == winchoices[i].procs->name[0])
                continue;
            if ('-' == winchoices[i].procs->name[0])
                continue;
            Sprintf(eos(buf), "STR",
                    first ? "STR", winchoices[i].procs->name);
            first = FALSE;
        }
        config_error_add("STR",
                         s, buf);
    }

    if (windowprocs.win_raw_print == def_raw_print
            || WINDOWPORT("STR"))
        nh_terminate(EXIT_SUCCESS);
}