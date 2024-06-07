static int do_print_sigalgs(BIO *out, SSL *s, int client, int shared)
	{
	int i, nsig;
	if (shared)
		nsig = SSL_get_shared_sigalgs(s, -1, NULL, NULL, NULL,
							NULL, NULL);
	else
		nsig = SSL_get_sigalgs(s, -1, NULL, NULL, NULL, NULL, NULL);
	if (nsig == 0)
		return 1;

	if (shared)
		BIO_puts(out, "STR");

	if (client)
		BIO_puts(out, "STR");
	BIO_puts(out, "STR");
	for (i = 0; i < nsig; i++)
		{
		int hash_nid, sign_nid;
		unsigned char rhash, rsign;
		const char *sstr = NULL;
		if (shared)
			SSL_get_shared_sigalgs(s, i, &sign_nid, &hash_nid, NULL,
							&rsign, &rhash);
		else
			SSL_get_sigalgs(s, i, &sign_nid, &hash_nid, NULL,
							&rsign, &rhash);
		if (i)
			BIO_puts(out, "STR");
		if (sign_nid == EVP_PKEY_RSA)
			sstr = "STR";
		else if(sign_nid == EVP_PKEY_DSA)
			sstr = "STR";
		else if(sign_nid == EVP_PKEY_EC)
			sstr = "STR";
		if (sstr)
			BIO_printf(out,"STR", sstr);
		else
			BIO_printf(out,"STR", (int)rsign);
		if (hash_nid != NID_undef)
			BIO_printf(out, "STR", OBJ_nid2sn(hash_nid));
		else
			BIO_printf(out,"STR", (int)rhash);
		}
	BIO_puts(out, "STR");
	return 1;
	}