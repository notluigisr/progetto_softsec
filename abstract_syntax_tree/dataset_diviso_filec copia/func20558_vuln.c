static int init_ssl_connection(SSL *con)
	{
	int i;
	const char *str;
	X509 *peer;
	long verify_error;
	MS_STATIC char buf[BUFSIZ];

	if ((i=SSL_accept(con)) <= 0)
		{
		if (BIO_sock_should_retry(i))
			{
			BIO_printf(bio_s_out,"STR");
			return(1);
			}

		BIO_printf(bio_err,"STR");
		verify_error=SSL_get_verify_result(con);
		if (verify_error != X509_V_OK)
			{
			BIO_printf(bio_err,"STR",
				X509_verify_cert_error_string(verify_error));
			}
		else
			ERR_print_errors(bio_err);
		return(0);
		}

	PEM_write_bio_SSL_SESSION(bio_s_out,SSL_get_session(con));

	peer=SSL_get_peer_certificate(con);
	if (peer != NULL)
		{
		BIO_printf(bio_s_out,"STR");
		PEM_write_bio_X509(bio_s_out,peer);
		X509_NAME_oneline(X509_get_subject_name(peer),buf,sizeof buf);
		BIO_printf(bio_s_out,"STR",buf);
		X509_NAME_oneline(X509_get_issuer_name(peer),buf,sizeof buf);
		BIO_printf(bio_s_out,"STR",buf);
		X509_free(peer);
		}

	if (SSL_get_shared_ciphers(con,buf,sizeof buf) != NULL)
		BIO_printf(bio_s_out,"STR",buf);
	str=SSL_CIPHER_get_name(SSL_get_current_cipher(con));
	BIO_printf(bio_s_out,"STR");
	if (con->hit) BIO_printf(bio_s_out,"STR");
	if (SSL_ctrl(con,SSL_CTRL_GET_FLAGS,0,NULL) &
		TLS1_FLAGS_TLS_PADDING_BUG)
		BIO_printf(bio_s_out,"STR");
#ifndef OPENSSL_NO_KRB5
	if (con->kssl_ctx->client_princ != NULL)
		{
		BIO_printf(bio_s_out,"STR",
			con->kssl_ctx->client_princ);
		}
#endif 
	BIO_printf(bio_s_out, "STR",
		      SSL_get_secure_renegotiation_support(con) ? "STR");
	return(1);
	}