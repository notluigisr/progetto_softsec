static int create_listener(struct listener_data *ifdata)
{
	int err, index;

	err = create_dns_listener(IPPROTO_UDP, ifdata);
	if ((err & UDP_FAILED) == UDP_FAILED)
		return -EIO;

	err |= create_dns_listener(IPPROTO_TCP, ifdata);
	if ((err & TCP_FAILED) == TCP_FAILED) {
		destroy_udp_listener(ifdata);
		return -EIO;
	}

	index = connman_inet_ifindex("STR");
	if (ifdata->index == index) {
		if ((err & IPv6_FAILED) != IPv6_FAILED)
			__connman_resolvfile_append(index, NULL, "STR");

		if ((err & IPv4_FAILED) != IPv4_FAILED)
			__connman_resolvfile_append(index, NULL, "STR");
	}

	return 0;
}