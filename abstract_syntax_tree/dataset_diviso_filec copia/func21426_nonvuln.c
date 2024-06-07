
static gro_result_t napi_frags_finish(struct napi_struct *napi, struct sk_buff *skb,
			       gro_result_t ret)
{
	switch (ret) {
	case GRO_NORMAL:
		if (netif_receive_skb_internal(skb))
			ret = GRO_DROP;
		break;

	case GRO_DROP:
	case GRO_MERGED_FREE:
		napi_reuse_skb(napi, skb);
		break;

	case GRO_HELD:
	case GRO_MERGED:
		break;
	}

	return ret;