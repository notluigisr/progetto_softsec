static int calipso_sock_setattr(struct sock *sk,
				const struct calipso_doi *doi_def,
				const struct netlbl_lsm_secattr *secattr)
{
	int ret_val;
	struct ipv6_opt_hdr *old, *new;
	struct ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	old = NULL;
	if (txopts)
		old = txopts->hopopt;

	new = calipso_opt_insert(old, doi_def, secattr);
	txopt_put(txopts);
	if (IS_ERR(new))
		return PTR_ERR(new);

	ret_val = calipso_opt_update(sk, new);

	kfree(new);
	return ret_val;
}