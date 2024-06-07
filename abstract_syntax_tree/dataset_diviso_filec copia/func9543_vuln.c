static u32 __ipv6_select_ident(struct net *net,
			       const struct in6_addr *dst,
			       const struct in6_addr *src)
{
	const struct {
		struct in6_addr dst;
		struct in6_addr src;
	} __aligned(SIPHASH_ALIGNMENT) combined = {
		.dst = *dst,
		.src = *src,
	};
	u32 hash, id;

	
	if (unlikely(siphash_key_is_zero(&net->ipv4.ip_id_key)))
		get_random_bytes(&net->ipv4.ip_id_key,
				 sizeof(net->ipv4.ip_id_key));

	hash = siphash(&combined, sizeof(combined), &net->ipv4.ip_id_key);

	
	id = ip_idents_reserve(hash, 1);
	if (unlikely(!id))
		id = 1 << 31;

	return id;
}