__skb_flow_dissect_ipv4(const struct sk_buff *skb,
			struct flow_dissector *flow_dissector,
			void *target_container, void *data, const struct iphdr *iph)
{
	struct flow_dissector_key_ip *key_ip;

	if (!dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IP))
		return;

	key_ip = skb_flow_dissector_target(flow_dissector,
					   FLOW_DISSECTOR_KEY_IP,
					   target_container);
	key_ip->tos = iph->tos;
	key_ip->ttl = iph->ttl;
}