static bool context_has_no_new_privileges(const ExecContext *c) {
        assert(c);

        if (c->no_new_privileges)
                return true;

        if (have_effective_cap(CAP_SYS_ADMIN)) 
                return false;

        
        return context_has_address_families(c) ||
                c->memory_deny_write_execute ||
                c->restrict_realtime ||
                exec_context_restrict_namespaces_set(c) ||
                c->protect_kernel_tunables ||
                c->protect_kernel_modules ||
                c->private_devices ||
                context_has_syscall_filters(c) ||
                !set_isempty(c->syscall_archs) ||
                c->lock_personality ||
                c->protect_hostname;
}