static inline u32 ___skb_get_hash(const struct sk_buff *skb,
				  struct flow_keys *keys, u32 keyval)
{
	skb_flow_dissect_flow_keys(skb, keys,
				   FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);

	return __flow_hash_from_keys(keys, keyval);
}