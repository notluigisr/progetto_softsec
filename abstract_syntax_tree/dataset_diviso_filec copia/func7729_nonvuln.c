char *SRP_create_verifier(const char *user, const char *pass, char **salt,
						  char **verifier, const char *N, const char *g)
	{
	int len;
	char * result=NULL;
	char *vf;
	BIGNUM *N_bn = NULL, *g_bn = NULL, *s = NULL, *v = NULL;
	unsigned char tmp[MAX_LEN];
	unsigned char tmp2[MAX_LEN];
	char * defgNid = NULL;

	if ((user == NULL)||
		(pass == NULL)||
		(salt == NULL)||
		(verifier == NULL))
		goto err;

	if (N)
		{
		if (!(len = t_fromb64(tmp, N))) goto err;
		N_bn = BN_bin2bn(tmp,len,NULL);
		if (!(len = t_fromb64(tmp, g))) goto err;
		g_bn = BN_bin2bn(tmp, len, NULL);
		defgNid = "STR";
		}
	else
		{ 
		SRP_gN * gN = SRP_get_gN_by_id(g, NULL) ;
		if (gN == NULL)
			goto err;
		N_bn = gN->N;
		g_bn = gN->g;
		defgNid = gN->id;
		}

	if (*salt == NULL)
		{
		RAND_pseudo_bytes(tmp2, SRP_RANDOM_SALT_LEN);

		s = BN_bin2bn(tmp2, SRP_RANDOM_SALT_LEN, NULL);
		}
	else
		{
		if (!(len = t_fromb64(tmp2, *salt)))
			goto err;
		s = BN_bin2bn(tmp2,len,NULL);
		}


	if(!SRP_create_verifier_BN(user, pass, &s, &v, N_bn, g_bn)) goto err;

	BN_bn2bin(v,tmp);
	if (((vf = OPENSSL_malloc(BN_num_bytes(v)*2)) == NULL))
		goto err;
	t_tob64(vf, tmp, BN_num_bytes(v));

	*verifier = vf;
	if (*salt == NULL)
		{
		char *tmp_salt;

		if ((tmp_salt = OPENSSL_malloc(SRP_RANDOM_SALT_LEN*2)) == NULL)
			{
			OPENSSL_free(vf);
			goto err;
			}
		t_tob64(tmp_salt,tmp2,SRP_RANDOM_SALT_LEN);
		*salt = tmp_salt;
		}

	result=defgNid;

err:
	if(N)
		{
		BN_free(N_bn);
		BN_free(g_bn);
		}
	return result;
	}