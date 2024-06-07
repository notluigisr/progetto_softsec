static int link_acquire_conf(Link *link) {
        int r;

        assert(link);
        assert(link->network);
        assert(link->manager);
        assert(link->manager->event);

        if (link_ipv4ll_enabled(link)) {
                assert(link->ipv4ll);

                log_link_debug(link, "STR");

                r = sd_ipv4ll_start(link->ipv4ll);
                if (r < 0)
                        return log_link_warning_errno(link, r, "STR");
        }

        if (link_dhcp4_enabled(link)) {
                assert(link->dhcp_client);

                log_link_debug(link, "STR");

                r = sd_dhcp_client_start(link->dhcp_client);
                if (r < 0)
                        return log_link_warning_errno(link, r, "STR");
        }

        if (link_dhcp6_enabled(link)) {
                assert(link->ndisc_router_discovery);

                log_link_debug(link, "STR");

                r = sd_ndisc_router_discovery_start(link->ndisc_router_discovery);
                if (r < 0)
                        return log_link_warning_errno(link, r, "STR");
        }

        if (link_lldp_enabled(link)) {
                assert(link->lldp);

                log_link_debug(link, "STR");

                r = sd_lldp_start(link->lldp);
                if (r < 0)
                        return log_link_warning_errno(link, r, "STR");
        }

        return 0;
}