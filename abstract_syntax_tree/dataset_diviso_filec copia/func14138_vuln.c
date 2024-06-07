void dns_server_unlink(DnsServer *s) {
        assert(s);
        assert(s->manager);

        

        if (!s->linked)
                return;

        switch (s->type) {

        case DNS_SERVER_LINK:
                assert(s->link);
                assert(s->link->n_dns_servers > 0);
                LIST_REMOVE(servers, s->link->dns_servers, s);
                s->link->n_dns_servers--;
                break;

        case DNS_SERVER_SYSTEM:
                assert(s->manager->n_dns_servers > 0);
                LIST_REMOVE(servers, s->manager->dns_servers, s);
                s->manager->n_dns_servers--;
                break;

        case DNS_SERVER_FALLBACK:
                assert(s->manager->n_dns_servers > 0);
                LIST_REMOVE(servers, s->manager->fallback_dns_servers, s);
                s->manager->n_dns_servers--;
                break;
        default:
                assert_not_reached("STR");
        }

        s->linked = false;

        if (s->link && s->link->current_dns_server == s)
                link_set_dns_server(s->link, NULL);

        if (s->manager->current_dns_server == s)
                manager_set_dns_server(s->manager, NULL);

        dns_server_unref(s);
}