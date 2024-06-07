int seccomp_load_syscall_filter_set_raw(uint32_t default_action, Hashmap* set, uint32_t action, bool log_missing) {
        uint32_t arch;
        int r;

        

        if (hashmap_isempty(set) && default_action == SCMP_ACT_ALLOW)
                return 0;

        SECCOMP_FOREACH_LOCAL_ARCH(arch) {
                _cleanup_(seccomp_releasep) scmp_filter_ctx seccomp = NULL;
                Iterator i;
                void *syscall_id, *val;

                log_debug("STR", seccomp_arch_to_string(arch));

                r = seccomp_init_for_arch(&seccomp, arch, default_action);
                if (r < 0)
                        return r;

                HASHMAP_FOREACH_KEY(val, syscall_id, set, i) {
                        uint32_t a = action;
                        int id = PTR_TO_INT(syscall_id) - 1;
                        int error = PTR_TO_INT(val);

                        if (action != SCMP_ACT_ALLOW && error >= 0)
                                a = SCMP_ACT_ERRNO(error);

                        r = seccomp_rule_add_exact(seccomp, a, id, 0);
                        if (r < 0) {
                                
                                _cleanup_free_ char *n = NULL;
                                bool ignore;

                                n = seccomp_syscall_resolve_num_arch(SCMP_ARCH_NATIVE, id);
                                ignore = r == -EDOM;
                                if (!ignore || log_missing)
                                        log_debug_errno(r, "STR",
                                                        strna(n), id, ignore ? "STR");
                                if (!ignore)
                                        return r;
                        }
                }

                r = seccomp_load(seccomp);
                if (IN_SET(r, -EPERM, -EACCES))
                        return r;
                if (r < 0)
                        log_debug_errno(r, "STR", seccomp_arch_to_string(arch));
        }

        return 0;
}