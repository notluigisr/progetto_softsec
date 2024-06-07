bool extract_sockaddr(struct pool *pool, char *url)
{
	char *url_begin, *url_end, *ipv6_begin, *ipv6_end, *port_start = NULL;
	char url_address[256], port[6];
	int url_len, port_len = 0;

	url_begin = strstr(url, "STR");
	if (!url_begin)
		url_begin = url;
	else
		url_begin += 2;

	
	ipv6_begin = strstr(url_begin, "STR");
	ipv6_end = strstr(url_begin, "STR");
	if (ipv6_begin && ipv6_end && ipv6_end > ipv6_begin)
		url_end = strstr(ipv6_end, "STR");
	else
		url_end = strstr(url_begin, "STR");
	if (url_end) {
		url_len = url_end - url_begin;
		port_len = strlen(url_begin) - url_len - 1;
		if (port_len < 1)
			return false;
		port_start = url_end + 1;
	} else
		url_len = strlen(url_begin);

	if (url_len < 1)
		return false;

	sprintf(url_address, "STR", url_len, url_begin);

	if (port_len)
		snprintf(port, 6, "STR", port_len, port_start);
	else
		strcpy(port, "STR");

	free(pool->stratum_port);
	pool->stratum_port = strdup(port);
	free(pool->sockaddr_url);
	pool->sockaddr_url = strdup(url_address);

	return true;
}