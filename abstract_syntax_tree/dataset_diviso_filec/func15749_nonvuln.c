static int smack_sk_alloc_security(struct sock *sk, int family, gfp_t gfp_flags)
{
	char *csp = current_security();
	struct socket_smack *ssp;

	ssp = kzalloc(sizeof(struct socket_smack), gfp_flags);
	if (ssp == NULL)
		return -ENOMEM;

	ssp->smk_in = csp;
	ssp->smk_out = csp;
	ssp->smk_packet[0] = '\0';

	sk->sk_security = ssp;

	return 0;
}