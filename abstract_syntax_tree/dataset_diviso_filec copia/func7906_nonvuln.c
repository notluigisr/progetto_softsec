int sctp_do_peeloff(struct sock *sk, sctp_assoc_t id, struct socket **sockp)
{
	struct sctp_association *asoc = sctp_id2assoc(sk, id);
	struct sctp_sock *sp = sctp_sk(sk);
	struct socket *sock;
	int err = 0;

	
	if (!net_eq(current->nsproxy->net_ns, sock_net(sk)))
		return -EINVAL;

	if (!asoc)
		return -EINVAL;

	
	if (!sctp_style(sk, UDP))
		return -EINVAL;

	
	err = sock_create(sk->sk_family, SOCK_SEQPACKET, IPPROTO_SCTP, &sock);
	if (err < 0)
		return err;

	sctp_copy_sock(sock->sk, sk, asoc);

	
	sp->pf->to_sk_daddr(&asoc->peer.primary_addr, sk);
	sp->pf->copy_ip_options(sk, sock->sk);

	
	err = sctp_sock_migrate(sk, sock->sk, asoc,
				SCTP_SOCKET_UDP_HIGH_BANDWIDTH);
	if (err) {
		sock_release(sock);
		sock = NULL;
	}

	*sockp = sock;

	return err;
}