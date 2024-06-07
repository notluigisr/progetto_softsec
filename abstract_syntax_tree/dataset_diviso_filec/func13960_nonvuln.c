
static inline bool skb_flow_dissect(const struct sk_buff *skb,
				    struct flow_dissector *flow_dissector,
				    void *target_container, unsigned int flags)
{
	return __skb_flow_dissect(skb, flow_dissector, target_container,
				  NULL, 0, 0, 0, flags);