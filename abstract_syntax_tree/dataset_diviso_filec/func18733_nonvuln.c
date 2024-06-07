int SRP_generate_client_master_secret(SSL *s,unsigned char *master_key)
	{
	BIGNUM *x = NULL, *u = NULL, *K = NULL;
	int ret = -1, tmp_len;
	char *passwd = NULL;
	unsigned char *tmp = NULL;

	
	if (SRP_Verify_B_mod_N(s->srp_ctx.B,s->srp_ctx.N)==0) goto err;
	if (!(u = SRP_Calc_u(s->srp_ctx.A,s->srp_ctx.B,s->srp_ctx.N))) goto err;
	if (s->srp_ctx.SRP_give_srp_client_pwd_callback == NULL) goto err;
	if (!(passwd = s->srp_ctx.SRP_give_srp_client_pwd_callback(s, s->srp_ctx.SRP_cb_arg))) goto err;
	if (!(x = SRP_Calc_x(s->srp_ctx.s,s->srp_ctx.login,passwd))) goto err;
	if (!(K = SRP_Calc_client_key(s->srp_ctx.N, s->srp_ctx.B, s->srp_ctx.g, x, s->srp_ctx.a, u))) goto err;

	tmp_len = BN_num_bytes(K);
	if ((tmp = OPENSSL_malloc(tmp_len)) == NULL) goto err;
	BN_bn2bin(K, tmp);
	ret = s->method->ssl3_enc->generate_master_secret(s,master_key,tmp,tmp_len);
err:
	if (tmp)
		{
		OPENSSL_cleanse(tmp,tmp_len) ;
		OPENSSL_free(tmp);
		}
	BN_clear_free(K);
	BN_clear_free(x);
	if (passwd)
		{
		OPENSSL_cleanse(passwd,strlen(passwd)) ;
		OPENSSL_free(passwd);
		}
	BN_clear_free(u);
	return ret;
	}