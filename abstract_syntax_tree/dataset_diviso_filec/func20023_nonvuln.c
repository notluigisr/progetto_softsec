				 unsigned int length, gfp_t gfp_mask);
static inline struct sk_buff *napi_alloc_skb(struct napi_struct *napi,
					     unsigned int length)
{
	return __napi_alloc_skb(napi, length, GFP_ATOMIC);