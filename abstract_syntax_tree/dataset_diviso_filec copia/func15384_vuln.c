static int packet_diag_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	int num = 0, s_num = cb->args[0];
	struct packet_diag_req *req;
	struct net *net;
	struct sock *sk;
	bool may_report_filterinfo;

	net = sock_net(skb->sk);
	req = nlmsg_data(cb->nlh);
	may_report_filterinfo = ns_capable(net->user_ns, CAP_NET_ADMIN);

	mutex_lock(&net->packet.sklist_lock);
	sk_for_each(sk, &net->packet.sklist) {
		if (!net_eq(sock_net(sk), net))
			continue;
		if (num < s_num)
			goto next;

		if (sk_diag_fill(sk, skb, req,
				 may_report_filterinfo,
				 sk_user_ns(NETLINK_CB(cb->skb).sk),
				 NETLINK_CB(cb->skb).portid,
				 cb->nlh->nlmsg_seq, NLM_F_MULTI,
				 sock_i_ino(sk)) < 0)
			goto done;
next:
		num++;
	}
done:
	mutex_unlock(&net->packet.sklist_lock);
	cb->args[0] = num;

	return skb->len;
}