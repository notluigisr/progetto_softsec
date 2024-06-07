static int ssl_get_server_cert_index(const SSL *s)
	{
	int idx;
	idx = ssl_cipher_get_cert_index(s->s3->tmp.new_cipher);
	if (idx == SSL_PKEY_RSA_ENC && !s->cert->pkeys[SSL_PKEY_RSA_ENC].x509)
		idx = SSL_PKEY_RSA_SIGN;
	if (idx == -1)
		SSLerr(SSL_F_SSL_GET_SERVER_CERT_INDEX,ERR_R_INTERNAL_ERROR);
	return idx;
	}