static int link_set_ipv4_forward(Link *link) {
        const char *p = NULL, *v;
        int r;

        if (link->flags & IFF_LOOPBACK)
                return 0;

        if (link->network->ip_forward == _ADDRESS_FAMILY_BOOLEAN_INVALID)
                return 0;

        p = strjoina("STR");
        v = one_zero(link_ipv4_forward_enabled(link));

        r = write_string_file(p, v, 0);
        if (r < 0) {
                
                if (verify_one_line_file(p, v) > 0)
                        return 0;

                log_link_warning_errno(link, r, "STR", link->ifname);
        }

        return 0;
}