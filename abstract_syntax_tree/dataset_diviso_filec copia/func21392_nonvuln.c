static int SRP_Verify_N_and_g(const BIGNUM *N, const BIGNUM *g)
	{
	BN_CTX *bn_ctx = BN_CTX_new();
	BIGNUM *p = BN_new();
	BIGNUM *r = BN_new();
	int ret =
		g != NULL && N != NULL && bn_ctx != NULL && BN_is_odd(N) &&
		BN_is_prime(N,SRP_NUMBER_ITERATIONS_FOR_PRIME,NULL,bn_ctx,NULL) &&
		p != NULL && BN_rshift1(p, N) &&

		
		BN_is_prime(p,SRP_NUMBER_ITERATIONS_FOR_PRIME,NULL,bn_ctx,NULL) &&
		r != NULL &&

		
		BN_mod_exp(r, g, p, N, bn_ctx) &&
		BN_add_word(r, 1) &&
		BN_cmp(r, N) == 0;

	if(r)
		BN_free(r);
	if(p)
		BN_free(p);
	if(bn_ctx)
		BN_CTX_free(bn_ctx);
	return ret;
	}