int avahi_mdns_mcast_join_ipv4(int fd, const AvahiIPv4Address *a, int idx, int join) {
#ifdef HAVE_STRUCT_IP_MREQN
    struct ip_mreqn mreq;
#else
    struct ip_mreq mreq;
#endif
    struct sockaddr_in sa;

    assert(fd >= 0);
    assert(idx >= 0);
    assert(a);

    memset(&mreq, 0, sizeof(mreq));
#ifdef HAVE_STRUCT_IP_MREQN
    mreq.imr_ifindex = idx;
    mreq.imr_address.s_addr = a->address;
#else
    mreq.imr_interface.s_addr = a->address;
#endif
    mdns_mcast_group_ipv4(&sa);
    mreq.imr_multiaddr = sa.sin_addr;

    
    if (join)
        setsockopt(fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));

    if (setsockopt(fd, IPPROTO_IP, join ? IP_ADD_MEMBERSHIP : IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        avahi_log_warn("STR", strerror(errno));
        return -1;
    }

    return 0;
}