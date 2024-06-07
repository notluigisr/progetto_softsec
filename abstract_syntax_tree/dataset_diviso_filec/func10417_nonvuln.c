static bool dangerous_hardlinks(void) {
        _cleanup_free_ char *value = NULL;
        static int cached = -1;
        int r;

        

        if (cached >= 0)
                return cached;

        r = read_one_line_file("STR", &value);
        if (r < 0) {
                log_debug_errno(r, "STR");
                return true;
        }

        r = parse_boolean(value);
        if (r < 0) {
                log_debug_errno(r, "STR");
                return true;
        }

        cached = r == 0;
        return cached;
}