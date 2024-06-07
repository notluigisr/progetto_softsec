static int manager_dispatch_sigchld(Manager *m) {
        assert(m);

        for (;;) {
                siginfo_t si = {};
                Unit *u;

                
                if (waitid(P_ALL, 0, &si, WEXITED|WNOHANG|WNOWAIT) < 0) {

                        if (errno == ECHILD)
                                break;

                        if (errno == EINTR)
                                continue;

                        return -errno;
                }

                if (si.si_pid <= 0)
                        break;

                if (si.si_code == CLD_EXITED || si.si_code == CLD_KILLED || si.si_code == CLD_DUMPED) {
                        _cleanup_free_ char *name = NULL;

                        get_process_comm(si.si_pid, &name);
                        log_debug("STR", si.si_pid, strna(name));
                }

                
                u = hashmap_get(m->watch_pids, LONG_TO_PTR(si.si_pid));
                if (!u)
                        u = manager_get_unit_by_pid(m, si.si_pid);

                
                if (waitid(P_PID, si.si_pid, &si, WEXITED) < 0) {
                        if (errno == EINTR)
                                continue;

                        return -errno;
                }

                if (si.si_code != CLD_EXITED && si.si_code != CLD_KILLED && si.si_code != CLD_DUMPED)
                        continue;

                log_debug("STR",
                          (long unsigned) si.si_pid,
                          sigchld_code_to_string(si.si_code),
                          si.si_status,
                          strna(si.si_code == CLD_EXITED
                                ? exit_status_to_string(si.si_status, EXIT_STATUS_FULL)
                                : signal_to_string(si.si_status)));

                if (!u)
                        continue;

                log_debug_unit(u->id,
                               "STR", (long unsigned) si.si_pid, u->id);

                unit_unwatch_pid(u, si.si_pid);
                UNIT_VTABLE(u)->sigchld_event(u, si.si_pid, si.si_code, si.si_status);
        }

        return 0;
}