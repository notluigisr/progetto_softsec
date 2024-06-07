int skb_checksum_help(struct sk_buff *skb, int inward)
{
	unsigned int csum;
	int ret = 0, offset = skb->h.raw - skb->data;

	if (inward) {
		skb->ip_summed = CHECKSUM_NONE;
		goto out;
	}

	if (skb_cloned(skb)) {
		ret = pskb_expand_head(skb, 0, 0, GFP_ATOMIC);
		if (ret)
			goto out;
	}

	if (offset > (int)skb->len)
		BUG();
	csum = skb_checksum(skb, offset, skb->len-offset, 0);

	offset = skb->tail - skb->h.raw;
	if (offset <= 0)
		BUG();
	if (skb->csum + 2 > offset)
		BUG();

	*(u16*)(skb->h.raw + skb->csum) = csum_fold(csum);
	skb->ip_summed = CHECKSUM_NONE;
out:	
	return ret;
}