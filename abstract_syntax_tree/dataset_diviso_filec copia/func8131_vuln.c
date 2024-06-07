SSL_CTX *SSL_CTX_new(const SSL_METHOD *meth)
	{
	SSL_CTX *ret=NULL;
	
	if (meth == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_NULL_SSL_METHOD_PASSED);
		return(NULL);
		}

	if (SSL_get_ex_data_X509_STORE_CTX_idx() < 0)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_X509_VERIFICATION_SETUP_PROBLEMS);
		goto err;
		}
	ret=(SSL_CTX *)OPENSSL_malloc(sizeof(SSL_CTX));
	if (ret == NULL)
		goto err;

	memset(ret,0,sizeof(SSL_CTX));

	ret->method=meth;

	ret->cert_store=NULL;
	ret->session_cache_mode=SSL_SESS_CACHE_SERVER;
	ret->session_cache_size=SSL_SESSION_CACHE_MAX_SIZE_DEFAULT;
	ret->session_cache_head=NULL;
	ret->session_cache_tail=NULL;

	
	ret->session_timeout=meth->get_timeout();

	ret->new_session_cb=0;
	ret->remove_session_cb=0;
	ret->get_session_cb=0;
	ret->generate_session_id=0;

	memset((char *)&ret->stats,0,sizeof(ret->stats));

	ret->references=1;
	ret->quiet_shutdown=0;




	ret->info_callback=NULL;

	ret->app_verify_callback=0;
	ret->app_verify_arg=NULL;

	ret->max_cert_list=SSL_MAX_CERT_LIST_DEFAULT;
	ret->read_ahead=0;
	ret->msg_callback=0;
	ret->msg_callback_arg=NULL;
	ret->verify_mode=SSL_VERIFY_NONE;
#if 0
	ret->verify_depth=-1; 
#endif
	ret->sid_ctx_length=0;
	ret->default_verify_callback=NULL;
	if ((ret->cert=ssl_cert_new()) == NULL)
		goto err;

	ret->default_passwd_callback=0;
	ret->default_passwd_callback_userdata=NULL;
	ret->client_cert_cb=0;
	ret->app_gen_cookie_cb=0;
	ret->app_verify_cookie_cb=0;

	ret->sessions=lh_SSL_SESSION_new();
	if (ret->sessions == NULL) goto err;
	ret->cert_store=X509_STORE_new();
	if (ret->cert_store == NULL) goto err;

	ssl_create_cipher_list(ret->method,
		&ret->cipher_list,&ret->cipher_list_by_id,
		SSL_DEFAULT_CIPHER_LIST);
	if (ret->cipher_list == NULL
	    || sk_SSL_CIPHER_num(ret->cipher_list) <= 0)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_LIBRARY_HAS_NO_CIPHERS);
		goto err2;
		}

	ret->param = X509_VERIFY_PARAM_new();
	if (!ret->param)
		goto err;

	if ((ret->rsa_md5=EVP_get_digestbyname("STR")) == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_UNABLE_TO_LOAD_SSL2_MD5_ROUTINES);
		goto err2;
		}
	if ((ret->md5=EVP_get_digestbyname("STR")) == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES);
		goto err2;
		}
	if ((ret->sha1=EVP_get_digestbyname("STR")) == NULL)
		{
		SSLerr(SSL_F_SSL_CTX_NEW,SSL_R_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES);
		goto err2;
		}

	if ((ret->client_CA=sk_X509_NAME_new_null()) == NULL)
		goto err;

	CRYPTO_new_ex_data(CRYPTO_EX_INDEX_SSL_CTX, ret, &ret->ex_data);

	ret->extra_certs=NULL;
	ret->comp_methods=SSL_COMP_get_compression_methods();

	ret->max_send_fragment = SSL3_RT_MAX_PLAIN_LENGTH;

#ifndef OPENSSL_NO_TLSEXT
	ret->tlsext_servername_callback = 0;
	ret->tlsext_servername_arg = NULL;
	
	if ((RAND_pseudo_bytes(ret->tlsext_tick_key_name, 16) <= 0)
		|| (RAND_bytes(ret->tlsext_tick_hmac_key, 16) <= 0)
		|| (RAND_bytes(ret->tlsext_tick_aes_key, 16) <= 0))
		ret->options |= SSL_OP_NO_TICKET;

	ret->tlsext_status_cb = 0;
	ret->tlsext_status_arg = NULL;

#endif
#ifndef OPENSSL_NO_PSK
	ret->psk_identity_hint=NULL;
	ret->psk_client_callback=NULL;
	ret->psk_server_callback=NULL;
#endif
	return(ret);
err:
	SSLerr(SSL_F_SSL_CTX_NEW,ERR_R_MALLOC_FAILURE);
err2:
	if (ret != NULL) SSL_CTX_free(ret);
	return(NULL);
	}