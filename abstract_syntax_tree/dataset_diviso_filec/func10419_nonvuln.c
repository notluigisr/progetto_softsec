AvahiSServiceResolver *avahi_s_service_resolver_prepare(
    AvahiServer *server,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    const char *name,
    const char *type,
    const char *domain,
    AvahiProtocol aprotocol,
    AvahiLookupFlags flags,
    AvahiSServiceResolverCallback callback,
    void* userdata) {

    AvahiSServiceResolver *r;
    AvahiKey *k;
    char n[AVAHI_DOMAIN_NAME_MAX];
    int ret;

    assert(server);
    assert(type);
    assert(callback);

    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, AVAHI_IF_VALID(interface), AVAHI_ERR_INVALID_INTERFACE);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, AVAHI_PROTO_VALID(protocol), AVAHI_ERR_INVALID_PROTOCOL);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, AVAHI_PROTO_VALID(aprotocol), AVAHI_ERR_INVALID_PROTOCOL);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, !domain || avahi_is_valid_domain_name(domain), AVAHI_ERR_INVALID_DOMAIN_NAME);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, !name || avahi_is_valid_service_name(name), AVAHI_ERR_INVALID_SERVICE_NAME);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, avahi_is_valid_service_type_strict(type), AVAHI_ERR_INVALID_SERVICE_TYPE);
    AVAHI_CHECK_VALIDITY_RETURN_NULL(server, AVAHI_FLAGS_VALID(flags, AVAHI_LOOKUP_USE_WIDE_AREA|AVAHI_LOOKUP_USE_MULTICAST|AVAHI_LOOKUP_NO_TXT|AVAHI_LOOKUP_NO_ADDRESS), AVAHI_ERR_INVALID_FLAGS);

    if (!domain)
        domain = server->domain_name;

    if ((ret = avahi_service_name_join(n, sizeof(n), name, type, domain)) < 0) {
        avahi_server_set_errno(server, ret);
        return NULL;
    }

    if (!(r = avahi_new(AvahiSServiceResolver, 1))) {
        avahi_server_set_errno(server, AVAHI_ERR_NO_MEMORY);
        return NULL;
    }

    r->server = server;
    r->service_name = avahi_strdup(name);
    r->service_type = avahi_normalize_name_strdup(type);
    r->domain_name = avahi_normalize_name_strdup(domain);
    r->callback = callback;
    r->userdata = userdata;
    r->address_protocol = aprotocol;
    r->srv_record = r->txt_record = r->address_record = NULL;
    r->srv_flags = r->txt_flags = r->address_flags = 0;
    r->interface = interface;
    r->protocol = protocol;
    r->user_flags = flags;
    r->record_browser_a = r->record_browser_aaaa = r->record_browser_srv = r->record_browser_txt = NULL;
    r->time_event = NULL;
    AVAHI_LLIST_PREPEND(AvahiSServiceResolver, resolver, server->service_resolvers, r);

    k = avahi_key_new(n, AVAHI_DNS_CLASS_IN, AVAHI_DNS_TYPE_SRV);
    r->record_browser_srv = avahi_s_record_browser_new(server, interface, protocol, k, flags & ~(AVAHI_LOOKUP_NO_TXT|AVAHI_LOOKUP_NO_ADDRESS), record_browser_callback, r);
    avahi_key_unref(k);

    if (!r->record_browser_srv) {
        avahi_s_service_resolver_free(r);
        return NULL;
    }

    if (!(flags & AVAHI_LOOKUP_NO_TXT)) {
        k = avahi_key_new(n, AVAHI_DNS_CLASS_IN, AVAHI_DNS_TYPE_TXT);
        r->record_browser_txt = avahi_s_record_browser_new(server, interface, protocol, k, flags & ~(AVAHI_LOOKUP_NO_TXT|AVAHI_LOOKUP_NO_ADDRESS),  record_browser_callback, r);
        avahi_key_unref(k);

        if (!r->record_browser_txt) {
            avahi_s_service_resolver_free(r);
            return NULL;
        }
    }

    start_timeout(r);

    return r;
}