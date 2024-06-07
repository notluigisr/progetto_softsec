void yang_str2ipv6(const char *value, struct in6_addr *addr)
{
	(void)inet_pton(AF_INET6, value, addr);
}