static int dns_transaction_emit_udp(DnsTransaction *t) {
        int r;

        assert(t);

        if (t->scope->protocol == DNS_PROTOCOL_DNS) {

                r = dns_transaction_pick_server(t);
                if (r < 0)
                        return r;

                if (t->current_feature_level < DNS_SERVER_FEATURE_LEVEL_UDP || DNS_SERVER_FEATURE_LEVEL_IS_TLS(t->current_feature_level))
                        return -EAGAIN; 

                if (!dns_server_dnssec_supported(t->server) && dns_type_is_dnssec(t->key->type))
                        return -EOPNOTSUPP;

                if (r > 0 || t->dns_udp_fd < 0) { 
                        int fd;

                        dns_transaction_close_connection(t);

                        fd = dns_scope_socket_udp(t->scope, t->server, 53);
                        if (fd < 0)
                                return fd;

                        r = sd_event_add_io(t->scope->manager->event, &t->dns_udp_event_source, fd, EPOLLIN, on_dns_packet, t);
                        if (r < 0) {
                                safe_close(fd);
                                return r;
                        }

                        (void) sd_event_source_set_description(t->dns_udp_event_source, "STR");
                        t->dns_udp_fd = fd;
                }

                r = dns_server_adjust_opt(t->server, t->sent, t->current_feature_level);
                if (r < 0)
                        return r;
        } else
                dns_transaction_close_connection(t);

        r = dns_scope_emit_udp(t->scope, t->dns_udp_fd, t->sent);
        if (r < 0)
                return r;

        dns_transaction_reset_answer(t);

        return 0;
}