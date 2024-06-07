is_ip_address(
	const char *	host,
	u_short		af,
	sockaddr_u *	addr
	)
{
	struct in_addr in4;
	struct addrinfo hints;
	struct addrinfo *result;
	struct sockaddr_in6 *resaddr6;
	char tmpbuf[128];
	char *pch;

	REQUIRE(host != NULL);
	REQUIRE(addr != NULL);

	ZERO_SOCK(addr);

	
	if (AF_UNSPEC == af || AF_INET == af)
		if (inet_pton(AF_INET, host, &in4) == 1) {
			AF(addr) = AF_INET;
			SET_ADDR4N(addr, in4.s_addr);

			return TRUE;
		}

	if (AF_UNSPEC == af || AF_INET6 == af)
		if (sizeof(tmpbuf) > strlen(host)) {
			if ('[' == host[0]) {
				strlcpy(tmpbuf, &host[1], sizeof(tmpbuf));
				pch = strchr(tmpbuf, ']');
				if (pch != NULL)
					*pch = '\0';
			} else {
				strlcpy(tmpbuf, host, sizeof(tmpbuf));
			}
			ZERO(hints);
			hints.ai_family = AF_INET6;
			hints.ai_flags |= AI_NUMERICHOST;
			if (getaddrinfo(tmpbuf, NULL, &hints, &result) == 0) {
				AF(addr) = AF_INET6;
				resaddr6 = UA_PTR(struct sockaddr_in6, result->ai_addr);
				SET_ADDR6N(addr, resaddr6->sin6_addr);
				SET_SCOPE(addr, resaddr6->sin6_scope_id);

				freeaddrinfo(result);
				return TRUE;
			}
		}
	
	return FALSE;
}