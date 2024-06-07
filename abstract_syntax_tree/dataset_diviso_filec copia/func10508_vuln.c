static int sr9700_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	struct sk_buff *sr_skb;
	int len;

	
	if (unlikely(skb->len < SR_RX_OVERHEAD)) {
		netdev_err(dev->net, "STR");
		return 0;
	}

	
	while (skb->len > SR_RX_OVERHEAD) {
		if (skb->data[0] != 0x40)
			return 0;

		
		len = (skb->data[1] | (skb->data[2] << 8)) - 4;

		if (len > ETH_FRAME_LEN)
			return 0;

		
		if (skb->len == (len + SR_RX_OVERHEAD))	{
			skb_pull(skb, 3);
			skb->len = len;
			skb_set_tail_pointer(skb, len);
			skb->truesize = len + sizeof(struct sk_buff);
			return 2;
		}

		
		sr_skb = skb_clone(skb, GFP_ATOMIC);
		if (!sr_skb)
			return 0;

		sr_skb->len = len;
		sr_skb->data = skb->data + 3;
		skb_set_tail_pointer(sr_skb, len);
		sr_skb->truesize = len + sizeof(struct sk_buff);
		usbnet_skb_return(dev, sr_skb);

		skb_pull(skb, len + SR_RX_OVERHEAD);
	}

	return 0;
}