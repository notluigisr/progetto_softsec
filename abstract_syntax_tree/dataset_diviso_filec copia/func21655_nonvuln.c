crypto_encrypt(
	const u_char *ptr,	
	u_int	vallen,		
	keyid_t	*cookie,	
	struct value *vp	
	)
{
	EVP_PKEY *pkey;		
	EVP_MD_CTX ctx;		
	tstamp_t tstamp;	
	u_int32	temp32;
	u_char *puch;

	
	pkey = d2i_PublicKey(EVP_PKEY_RSA, NULL, &ptr, vallen);
	if (pkey == NULL) {
		msyslog(LOG_ERR, "STR",
		    ERR_error_string(ERR_get_error(), NULL));
		return (XEVNT_PUB);
	}

	
	memset(vp, 0, sizeof(struct value));
	tstamp = crypto_time();
	vp->tstamp = htonl(tstamp);
	vp->fstamp = hostval.tstamp;
	vallen = EVP_PKEY_size(pkey);
	vp->vallen = htonl(vallen);
	vp->ptr = emalloc(vallen);
	puch = vp->ptr;
	temp32 = htonl(*cookie);
	if (RSA_public_encrypt(4, (u_char *)&temp32, puch,
	    pkey->pkey.rsa, RSA_PKCS1_OAEP_PADDING) <= 0) {
		msyslog(LOG_ERR, "STR",
		    ERR_error_string(ERR_get_error(), NULL));
		free(vp->ptr);
		EVP_PKEY_free(pkey);
		return (XEVNT_CKY);
	}
	EVP_PKEY_free(pkey);
	if (tstamp == 0)
		return (XEVNT_OK);

	vp->sig = emalloc(sign_siglen);
	EVP_SignInit(&ctx, sign_digest);
	EVP_SignUpdate(&ctx, (u_char *)&vp->tstamp, 12);
	EVP_SignUpdate(&ctx, vp->ptr, vallen);
	if (EVP_SignFinal(&ctx, vp->sig, &vallen, sign_pkey)) {
		INSIST(vallen <= sign_siglen);
		vp->siglen = htonl(vallen);
	}
	return (XEVNT_OK);
}