 */
__sum16 __skb_gro_checksum_complete(struct sk_buff *skb)
{
	__wsum wsum;
	__sum16 sum;

	wsum = skb_checksum(skb, skb_gro_offset(skb), skb_gro_len(skb), 0);

	
	sum = csum_fold(csum_add(NAPI_GRO_CB(skb)->csum, wsum));
	if (likely(!sum)) {
		if (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(skb->dev);
	}

	NAPI_GRO_CB(skb)->csum = wsum;
	NAPI_GRO_CB(skb)->csum_valid = 1;

	return sum;