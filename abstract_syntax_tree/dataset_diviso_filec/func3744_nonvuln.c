struct yang_data *yang_data_new_ip(const char *xpath, const struct ipaddr *addr)
{
	size_t sz = IS_IPADDR_V4(addr) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
	char value_str[sz];

	ipaddr2str(addr, value_str, sizeof(value_str));
	return yang_data_new(xpath, value_str);
}