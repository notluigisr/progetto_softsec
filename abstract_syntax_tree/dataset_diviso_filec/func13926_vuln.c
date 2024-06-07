STACK_OF(SSL_CIPHER) *ssl_bytes_to_cipher_list(SSL *s,unsigned char *p,int num,
					       STACK_OF(SSL_CIPHER) **skp)
	{
	const SSL_CIPHER *c;
	STACK_OF(SSL_CIPHER) *sk;
	int i,n;
	if (s->s3)
		s->s3->send_connection_binding = 0;

	n=ssl_put_cipher_by_char(s,NULL,NULL);
	if ((num%n) != 0)
		{
		SSLerr(SSL_F_SSL_BYTES_TO_CIPHER_LIST,SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST);
		return(NULL);
		}
	if ((skp == NULL) || (*skp == NULL))
		sk=sk_SSL_CIPHER_new_null(); 
	else
		{
		sk= *skp;
		sk_SSL_CIPHER_zero(sk);
		}

	if (s->cert->ciphers_raw)
		OPENSSL_free(s->cert->ciphers_raw);
	s->cert->ciphers_raw = BUF_memdup(p, num);
	if (s->cert->ciphers_raw == NULL)
		{
		SSLerr(SSL_F_SSL_BYTES_TO_CIPHER_LIST,ERR_R_MALLOC_FAILURE);
		goto err;
		}
	s->cert->ciphers_rawlen = (size_t)num;

	for (i=0; i<num; i+=n)
		{
		
		if (s->s3 && (n != 3 || !p[0]) &&
			(p[n-2] == ((SSL3_CK_SCSV >> 8) & 0xff)) &&
			(p[n-1] == (SSL3_CK_SCSV & 0xff)))
			{
			
			if (s->renegotiate)
				{
				SSLerr(SSL_F_SSL_BYTES_TO_CIPHER_LIST,SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING);
				ssl3_send_alert(s,SSL3_AL_FATAL,SSL_AD_HANDSHAKE_FAILURE); 
				goto err;
				}
			s->s3->send_connection_binding = 1;
			p += n;
#ifdef OPENSSL_RI_DEBUG
			fprintf(stderr, "STR");
#endif
			continue;
			}

		c=ssl_get_cipher_by_char(s,p);
		p+=n;
		if (c != NULL)
			{
			if (!sk_SSL_CIPHER_push(sk,c))
				{
				SSLerr(SSL_F_SSL_BYTES_TO_CIPHER_LIST,ERR_R_MALLOC_FAILURE);
				goto err;
				}
			}
		}

	if (skp != NULL)
		*skp=sk;
	return(sk);
err:
	if ((skp == NULL) || (*skp == NULL))
		sk_SSL_CIPHER_free(sk);
	return(NULL);
	}