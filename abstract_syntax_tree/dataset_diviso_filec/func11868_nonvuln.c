static void raw_err(struct sock *sk, struct sk_buff *skb, u32 info)
{
	struct inet_sock *inet = inet_sk(sk);
	const int type = icmp_hdr(skb)->type;
	const int code = icmp_hdr(skb)->code;
	int err = 0;
	int harderr = 0;

	
	if (!inet->recverr && sk->sk_state != TCP_ESTABLISHED)
		return;

	switch (type) {
	default:
	case ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		break;
	case ICMP_SOURCE_QUENCH:
		return;
	case ICMP_PARAMETERPROB:
		err = EPROTO;
		harderr = 1;
		break;
	case ICMP_DEST_UNREACH:
		err = EHOSTUNREACH;
		if (code > NR_ICMP_UNREACH)
			break;
		err = icmp_err_convert[code].errno;
		harderr = icmp_err_convert[code].fatal;
		if (code == ICMP_FRAG_NEEDED) {
			harderr = inet->pmtudisc != IP_PMTUDISC_DONT;
			err = EMSGSIZE;
		}
	}

	if (inet->recverr) {
		const struct iphdr *iph = (const struct iphdr *)skb->data;
		u8 *payload = skb->data + (iph->ihl << 2);

		if (inet->hdrincl)
			payload = skb->data;
		ip_icmp_error(sk, skb, err, 0, info, payload);
	}

	if (inet->recverr || harderr) {
		sk->sk_err = err;
		sk->sk_error_report(sk);
	}
}