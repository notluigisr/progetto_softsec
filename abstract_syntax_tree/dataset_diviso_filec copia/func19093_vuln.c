static unsigned int skb_gso_mac_seglen(const struct sk_buff *skb)
{
	unsigned int hdr_len = skb_transport_header(skb) - skb_mac_header(skb);
	return hdr_len + skb_gso_transport_seglen(skb);
}