CryptRsaDecrypt(
		TPM2B               *dOut,          
		TPM2B               *cIn,           
		OBJECT              *key,           
		TPMT_RSA_DECRYPT    *scheme,        
		const TPM2B         *label          
		)
{
    TPM_RC                 retVal;
    EVP_PKEY              *pkey = NULL;
    EVP_PKEY_CTX          *ctx = NULL;
    const EVP_MD          *md = NULL;
    const char            *digestname;
    size_t                 outlen;
    unsigned char         *tmp = NULL;

    
    pAssert(cIn != NULL && dOut != NULL && key != NULL);
    
    if(cIn->size != key->publicArea.unique.rsa.t.size)
        ERROR_RETURN(TPM_RC_SIZE);
    TEST(scheme->scheme);

    retVal = InitOpenSSLRSAPrivateKey(key, &pkey);
    if (retVal != TPM_RC_SUCCESS)
        return retVal;

    ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (ctx == NULL ||
        EVP_PKEY_decrypt_init(ctx) <= 0)
        ERROR_RETURN(TPM_RC_FAILURE);

    switch(scheme->scheme)
	{
	  case ALG_NULL_VALUE:  
            if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            break;
	  case ALG_RSAES_VALUE:
            if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            break;
	  case ALG_OAEP_VALUE:
            digestname = GetDigestNameByHashAlg(scheme->details.oaep.hashAlg);
            if (digestname == NULL)
                ERROR_RETURN(TPM_RC_VALUE);

            md = EVP_get_digestbyname(digestname);
            if (md == NULL ||
                EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0 ||
                EVP_PKEY_CTX_set_rsa_oaep_md(ctx, md) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);

            if (label->size > 0) {
                tmp = malloc(label->size);
                if (tmp == NULL)
                    ERROR_RETURN(TPM_RC_FAILURE);
                memcpy(tmp, label->buffer, label->size);
            }

            if (EVP_PKEY_CTX_set0_rsa_oaep_label(ctx, tmp, label->size) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            tmp = NULL;
            break;
	  default:
            ERROR_RETURN(TPM_RC_SCHEME);
            break;
	}

    outlen = cIn->size;
    if (EVP_PKEY_decrypt(ctx, dOut->buffer, &outlen,
                         cIn->buffer, cIn->size) <= 0)
        ERROR_RETURN(TPM_RC_FAILURE);

    dOut->size = outlen;

    retVal = TPM_RC_SUCCESS;

 Exit:
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    free(tmp);

    return retVal;
}