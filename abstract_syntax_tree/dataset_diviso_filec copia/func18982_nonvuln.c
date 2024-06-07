static inline void
__skb_set_sw_hash(struct sk_buff *skb, __u32 hash, bool is_l4)
{
	__skb_set_hash(skb, hash, true, is_l4);