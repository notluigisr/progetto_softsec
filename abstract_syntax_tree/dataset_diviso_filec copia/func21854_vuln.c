int ssl3_get_finished(SSL *s, int a, int b)
	{
	int al,i,ok;
	long n;
	unsigned char *p;

	 

	n=s->method->ssl_get_message(s,
		a,
		b,
		SSL3_MT_FINISHED,
		64, 
		&ok);

	if (!ok) return((int)n);

	
	if (!s->s3->change_cipher_spec)
		{
		al=SSL_AD_UNEXPECTED_MESSAGE;
		SSLerr(SSL_F_SSL3_GET_FINISHED,SSL_R_GOT_A_FIN_BEFORE_A_CCS);
		goto f_err;
		}
	s->s3->change_cipher_spec=0;

	p = (unsigned char *)s->init_msg;
	i = s->s3->tmp.peer_finish_md_len;

	if (i != n)
		{
		al=SSL_AD_DECODE_ERROR;
		SSLerr(SSL_F_SSL3_GET_FINISHED,SSL_R_BAD_DIGEST_LENGTH);
		goto f_err;
		}

	if (memcmp(p, s->s3->tmp.peer_finish_md, i) != 0)
		{
		al=SSL_AD_DECRYPT_ERROR;
		SSLerr(SSL_F_SSL3_GET_FINISHED,SSL_R_DIGEST_CHECK_FAILED);
		goto f_err;
		}

        
        if(s->type == SSL_ST_ACCEPT)
                {
                OPENSSL_assert(i <= EVP_MAX_MD_SIZE);
                memcpy(s->s3->previous_client_finished, 
                    s->s3->tmp.peer_finish_md, i);
                s->s3->previous_client_finished_len=i;
                }
        else
                {
                OPENSSL_assert(i <= EVP_MAX_MD_SIZE);
                memcpy(s->s3->previous_server_finished, 
                    s->s3->tmp.peer_finish_md, i);
                s->s3->previous_server_finished_len=i;
                }

	return(1);
f_err:
	ssl3_send_alert(s,SSL3_AL_FATAL,al);
	return(0);
	}