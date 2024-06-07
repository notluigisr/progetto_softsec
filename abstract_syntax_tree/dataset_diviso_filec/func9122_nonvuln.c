static const char* mount_propagation_flags_to_string_with_check(unsigned long n) {
        if (!IN_SET(n, 0, MS_SHARED, MS_PRIVATE, MS_SLAVE))
                return NULL;

        return mount_propagation_flags_to_string(n);
}