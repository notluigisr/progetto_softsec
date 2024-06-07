static inline int sctp_verify_addr(struct sock *sk, union sctp_addr *addr,
				   int len)
{
	struct sctp_af *af;

	
	af = sctp_sockaddr_af(sctp_sk(sk), addr, len);
	if (!af)
		return -EINVAL;

	
	if (!af->addr_valid(addr, sctp_sk(sk), NULL))
		return -EINVAL;

	if (!sctp_sk(sk)->pf->send_verify(sctp_sk(sk), (addr)))
		return -EINVAL;

	return 0;
}