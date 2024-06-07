static bool parse_reconnect(struct pool *pool, json_t *val)
{
	char *sockaddr_url, *stratum_port, *tmp;
	char *url, *port, address[256];

	memset(address, 0, 255);
	url = (char *)json_string_value(json_array_get(val, 0));
	if (!url)
		url = pool->sockaddr_url;
	else {
		char *dot_pool, *dot_reconnect;
		dot_pool = strchr(pool->sockaddr_url, '.');
		if (!dot_pool) {
			applog(LOG_ERR, "STR",
			       pool->sockaddr_url);
			return false;
		}
		dot_reconnect = strchr(url, '.');
		if (!dot_reconnect) {
			applog(LOG_ERR, "STR",
			       url);
			return false;
		}
		if (strcmp(dot_pool, dot_reconnect)) {
			applog(LOG_ERR, "STR",
				pool->sockaddr_url);
			return false;
		}
	}

	port = (char *)json_string_value(json_array_get(val, 1));
	if (!port)
		port = pool->stratum_port;

	sprintf(address, "STR", url, port);

	if (!extract_sockaddr(address, &sockaddr_url, &stratum_port))
		return false;

	applog(LOG_WARNING, "STR", pool->pool_no, address);

	clear_pool_work(pool);

	mutex_lock(&pool->stratum_lock);
	__suspend_stratum(pool);
	tmp = pool->sockaddr_url;
	pool->sockaddr_url = sockaddr_url;
	pool->stratum_url = pool->sockaddr_url;
	free(tmp);
	tmp = pool->stratum_port;
	pool->stratum_port = stratum_port;
	free(tmp);
	mutex_unlock(&pool->stratum_lock);

	if (!restart_stratum(pool)) {
		pool_failed(pool);
		return false;
	}

	return true;
}