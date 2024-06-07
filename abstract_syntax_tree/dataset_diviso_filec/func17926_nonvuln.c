static int load_certs_crls(BIO *err, const char *file, int format,
	const char *pass, ENGINE *e, const char *desc,
	STACK_OF(X509) **pcerts, STACK_OF(X509_CRL) **pcrls)
	{
	int i;
	BIO *bio;
	STACK_OF(X509_INFO) *xis = NULL;
	X509_INFO *xi;
	PW_CB_DATA cb_data;
	int rv = 0;

	cb_data.password = pass;
	cb_data.prompt_info = file;

	if (format != FORMAT_PEM)
		{
		BIO_printf(err,"STR", desc);
		return 0;
		}

	if (file == NULL)
		bio = BIO_new_fp(stdin,BIO_NOCLOSE);
	else
		bio = BIO_new_file(file, "STR");

	if (bio == NULL)
		{
		BIO_printf(err, "STR",
				desc, file ? file : "STR");
		ERR_print_errors(err);
		return 0;
		}

	xis = PEM_X509_INFO_read_bio(bio, NULL,
				(pem_password_cb *)password_callback, &cb_data);

	BIO_free(bio);

	if (pcerts)
		{
		*pcerts = sk_X509_new_null();
		if (!*pcerts)
			goto end;
		}

	if (pcrls)
		{
		*pcrls = sk_X509_CRL_new_null();
		if (!*pcrls)
			goto end;
		}

	for(i = 0; i < sk_X509_INFO_num(xis); i++)
		{
		xi = sk_X509_INFO_value (xis, i);
		if (xi->x509 && pcerts)
			{
			if (!sk_X509_push(*pcerts, xi->x509))
				goto end;
			xi->x509 = NULL;
			}
		if (xi->crl && pcrls)
			{
			if (!sk_X509_CRL_push(*pcrls, xi->crl))
				goto end;
			xi->crl = NULL;
			}
		}

	if (pcerts && sk_X509_num(*pcerts) > 0)
		rv = 1;

	if (pcrls && sk_X509_CRL_num(*pcrls) > 0)
		rv = 1;

	end:

	if (xis)
		sk_X509_INFO_pop_free(xis, X509_INFO_free);

	if (rv == 0)
		{
		if (pcerts)
			{
			sk_X509_pop_free(*pcerts, X509_free);
			*pcerts = NULL;
			}
		if (pcrls)
			{
			sk_X509_CRL_pop_free(*pcrls, X509_CRL_free);
			*pcrls = NULL;
			}
		BIO_printf(err,"STR",
				pcerts ? "STR");
		ERR_print_errors(err);
		}
	return rv;
	}