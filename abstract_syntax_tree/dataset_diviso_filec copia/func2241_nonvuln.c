static inline void dccp_connect_init(struct sock *sk)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct dst_entry *dst = __sk_dst_get(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	sk->sk_err = 0;
	sock_reset_flag(sk, SOCK_DONE);

	dccp_sync_mss(sk, dst_mtu(dst));

	
	dccp_update_gss(sk, dp->dccps_iss);
	dccp_set_seqno(&dp->dccps_awl, max48(dp->dccps_awl, dp->dccps_iss));

	
	dp->dccps_gar = dp->dccps_iss;

	icsk->icsk_retransmits = 0;
}