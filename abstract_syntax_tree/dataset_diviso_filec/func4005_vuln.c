int dccp_send_reset(struct sock *sk, enum dccp_reset_codes code)
{
	struct sk_buff *skb;
	
	int err = inet_sk_rebuild_header(sk);

	if (err != 0)
		return err;

	skb = sock_wmalloc(sk, sk->sk_prot->max_header, 1, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOBUFS;

	
	skb_reserve(skb, sk->sk_prot->max_header);
	DCCP_SKB_CB(skb)->dccpd_type	   = DCCP_PKT_RESET;
	DCCP_SKB_CB(skb)->dccpd_reset_code = code;

	return dccp_transmit_skb(sk, skb);
}