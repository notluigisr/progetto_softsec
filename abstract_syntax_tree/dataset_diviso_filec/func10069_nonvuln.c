static void calipso_req_delattr(struct request_sock *req)
{
	struct inet_request_sock *req_inet = inet_rsk(req);
	struct ipv6_opt_hdr *new;
	struct ipv6_txoptions *txopts;
	struct sock *sk = sk_to_full_sk(req_to_sk(req));

	if (!req_inet->ipv6_opt || !req_inet->ipv6_opt->hopopt)
		return;

	if (calipso_opt_del(req_inet->ipv6_opt->hopopt, &new))
		return; 

	txopts = ipv6_renew_options(sk, req_inet->ipv6_opt, IPV6_HOPOPTS, new);

	if (!IS_ERR(txopts)) {
		txopts = xchg(&req_inet->ipv6_opt, txopts);
		if (txopts) {
			atomic_sub(txopts->tot_len, &sk->sk_omem_alloc);
			txopt_put(txopts);
		}
	}
	kfree(new);
}