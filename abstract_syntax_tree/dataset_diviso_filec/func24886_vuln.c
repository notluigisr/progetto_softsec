static int link_stop_clients(Link *link) {
        int r = 0, k;

        assert(link);
        assert(link->manager);
        assert(link->manager->event);

        if (!link->network)
                return 0;

        if (link->dhcp_client) {
                k = sd_dhcp_client_stop(link->dhcp_client);
                if (k < 0)
                        r = log_link_warning_errno(link, r, "STR");
        }

        if (link->ipv4ll) {
                k = sd_ipv4ll_stop(link->ipv4ll);
                if (k < 0)
                        r = log_link_warning_errno(link, r, "STR");
        }

        if(link->ndisc_router_discovery) {
                if (link->dhcp6_client) {
                        k = sd_dhcp6_client_stop(link->dhcp6_client);
                        if (k < 0)
                                r = log_link_warning_errno(link, r, "STR");
                }

                k = sd_ndisc_stop(link->ndisc_router_discovery);
                if (k < 0)
                        r = log_link_warning_errno(link, r, "STR");
        }

        if (link->lldp) {
                k = sd_lldp_stop(link->lldp);
                if (k < 0)
                        r = log_link_warning_errno(link, r, "STR");
        }

        return r;
}