static inline void ep_set_busy_poll_napi_id(struct epitem *epi)
{
	struct eventpoll *ep;
	unsigned int napi_id;
	struct socket *sock;
	struct sock *sk;
	int err;

	if (!net_busy_loop_on())
		return;

	sock = sock_from_file(epi->ffd.file, &err);
	if (!sock)
		return;

	sk = sock->sk;
	if (!sk)
		return;

	napi_id = READ_ONCE(sk->sk_napi_id);
	ep = epi->ep;

	
	if (napi_id < MIN_NAPI_ID || napi_id == ep->napi_id)
		return;

	
	ep->napi_id = napi_id;
}