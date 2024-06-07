
int config_parse_line_max(
                const char* unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        size_t *sz = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue))
                
                *sz = DEFAULT_LINE_MAX;
        else {
                uint64_t v;

                r = parse_size(rvalue, 1024, &v);
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r, "STR", rvalue);
                        return 0;
                }

                if (v < 79) {
                        
                        log_syntax(unit, LOG_WARNING, filename, line, 0, "STR", rvalue);
                        *sz = 79;
                } else if (v > (uint64_t) (SSIZE_MAX-1)) {
                        
                        log_syntax(unit, LOG_WARNING, filename, line, 0, "STR", (uint64_t) (SSIZE_MAX-1), rvalue);
                        *sz = SSIZE_MAX-1;
                } else
                        *sz = (size_t) v;
        }

        return 0;