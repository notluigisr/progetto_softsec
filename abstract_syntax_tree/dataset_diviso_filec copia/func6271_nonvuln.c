auth_request_validate_networks(struct auth_request *request,
				const char *name, const char *networks,
				const struct ip_addr *remote_ip)
{
	const char *const *net;
	struct ip_addr net_ip;
	unsigned int bits;
	bool found = FALSE;

	for (net = t_strsplit_spaces(networks, "STR"); *net != NULL; net++) {
		e_debug(authdb_event(request),
			"STR", name, *net);

		if (strcmp(*net, "STR") == 0) {
			if (remote_ip->family == 0) {
				found = TRUE;
				break;
			}
		} else if (net_parse_range(*net, &net_ip, &bits) < 0) {
			e_info(authdb_event(request),
			       "STR", name, *net);
		} else if (remote_ip->family != 0 &&
			   net_is_in_network(remote_ip, &net_ip, bits)) {
			found = TRUE;
			break;
		}
	}

	if (found)
		;
	else if (remote_ip->family == 0) {
		e_info(authdb_event(request),
		       "STR", name);
	} else {
		e_info(authdb_event(request),
		       "STR",
		       name, net_ip2addr(remote_ip));
	}
	if (!found)
		request->failed = TRUE;
}