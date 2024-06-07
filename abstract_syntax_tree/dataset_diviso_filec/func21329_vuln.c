int ssl3_send_server_hello(SSL *s)
	{
	unsigned char *buf;
	unsigned char *p,*d;
	int i,sl;
	unsigned long l,Time;

	if (s->state == SSL3_ST_SW_SRVR_HELLO_A)
		{
		buf=(unsigned char *)s->init_buf->data;
		p=s->s3->server_random;
		Time=(unsigned long)time(NULL);			
		l2n(Time,p);
		if (RAND_pseudo_bytes(p,SSL3_RANDOM_SIZE-4) <= 0)
			return -1;
		
		d=p= &(buf[4]);

		*(p++)=s->version>>8;
		*(p++)=s->version&0xff;

		
		memcpy(p,s->s3->server_random,SSL3_RANDOM_SIZE);
		p+=SSL3_RANDOM_SIZE;

		
		if (!(s->ctx->session_cache_mode & SSL_SESS_CACHE_SERVER))
			s->session->session_id_length=0;

		sl=s->session->session_id_length;
		if (sl > (int)sizeof(s->session->session_id))
			{
			SSLerr(SSL_F_SSL3_SEND_SERVER_HELLO, ERR_R_INTERNAL_ERROR);
			return -1;
			}
		*(p++)=sl;
		memcpy(p,s->session->session_id,sl);
		p+=sl;

		
		i=ssl3_put_cipher_by_char(s->s3->tmp.new_cipher,p);
		p+=i;

		
#ifdef OPENSSL_NO_COMP
			*(p++)=0;
#else
		if (s->s3->tmp.new_compression == NULL)
			*(p++)=0;
		else
			*(p++)=s->s3->tmp.new_compression->id;
#endif
#ifndef OPENSSL_NO_TLSEXT
		if ((p = ssl_add_serverhello_tlsext(s, p, buf+SSL3_RT_MAX_PLAIN_LENGTH)) == NULL)
			{
			SSLerr(SSL_F_SSL3_SEND_SERVER_HELLO,ERR_R_INTERNAL_ERROR);
			return -1;
			}
#endif

		
		l=(p-d);
		d=buf;
		*(d++)=SSL3_MT_SERVER_HELLO;
		l2n3(l,d);

		s->state=SSL3_ST_CW_CLNT_HELLO_B;
		
		s->init_num=p-buf;
		s->init_off=0;
		}

	
	return(ssl3_do_write(s,SSL3_RT_HANDSHAKE));
	}