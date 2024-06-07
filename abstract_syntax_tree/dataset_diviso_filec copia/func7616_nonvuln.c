
static inline void skb_probe_transport_header(struct sk_buff *skb,
					      const int offset_hint)
{
	struct flow_keys keys;

	if (skb_transport_header_was_set(skb))
		return;
	else if (skb_flow_dissect_flow_keys(skb, &keys, 0))
		skb_set_transport_header(skb, keys.control.thoff);
	else
		skb_set_transport_header(skb, offset_hint);