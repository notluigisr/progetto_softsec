static int rt6_info_hash_nhsfn(unsigned int candidate_count,
			       const struct flowi6 *fl6)
{
	unsigned int val = fl6->flowi6_proto;

	val ^= ipv6_addr_hash(&fl6->daddr);
	val ^= ipv6_addr_hash(&fl6->saddr);

	
	switch (fl6->flowi6_proto) {
	case IPPROTO_UDP:
	case IPPROTO_TCP:
	case IPPROTO_SCTP:
		val ^= (__force u16)fl6->fl6_sport;
		val ^= (__force u16)fl6->fl6_dport;
		break;

	case IPPROTO_ICMPV6:
		val ^= (__force u16)fl6->fl6_icmp_type;
		val ^= (__force u16)fl6->fl6_icmp_code;
		break;
	}
	
	val ^= (__force u32)fl6->flowlabel;

	
	val = val ^ (val >> 7) ^ (val >> 12);
	return val % candidate_count;
}