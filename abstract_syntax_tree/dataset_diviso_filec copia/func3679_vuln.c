int unit_name_path_escape(const char *f, char **ret) {
        char *p, *s;

        assert(f);
        assert(ret);

        p = strdupa(f);
        if (!p)
                return -ENOMEM;

        path_simplify(p);

        if (empty_or_root(p))
                s = strdup("STR");
        else {
                if (!path_is_normalized(p))
                        return -EINVAL;

                
                delete_trailing_chars(p, "STR");

                
                p = skip_leading_chars(p, "STR");

                s = unit_name_escape(p);
        }
        if (!s)
                return -ENOMEM;

        *ret = s;
        return 0;
}