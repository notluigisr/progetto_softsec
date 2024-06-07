int ssl3_do_change_cipher_spec(SSL *s)
	{
	int i;
	const char *sender;
	int slen;

	if (s->state & SSL_ST_ACCEPT)
		i=SSL3_CHANGE_CIPHER_SERVER_READ;
	else
		i=SSL3_CHANGE_CIPHER_CLIENT_READ;

	if (s->s3->tmp.key_block == NULL)
		{
		if (s->session == NULL) 
			{
			
			SSLerr(SSL_F_SSL3_DO_CHANGE_CIPHER_SPEC,SSL_R_CCS_RECEIVED_EARLY);
			return (0);
			}

		s->session->cipher=s->s3->tmp.new_cipher;
		if (!s->method->ssl3_enc->setup_key_block(s)) return(0);
		}

	if (!s->method->ssl3_enc->change_cipher_state(s,i))
		return(0);

	
	if (s->state & SSL_ST_CONNECT)
		{
		sender=s->method->ssl3_enc->server_finished_label;
		slen=s->method->ssl3_enc->server_finished_label_len;
		}
	else
		{
		sender=s->method->ssl3_enc->client_finished_label;
		slen=s->method->ssl3_enc->client_finished_label_len;
		}

	i = s->method->ssl3_enc->final_finish_mac(s,
		sender,slen,s->s3->tmp.peer_finish_md);
	if (i == 0)
		{
		SSLerr(SSL_F_SSL3_DO_CHANGE_CIPHER_SPEC, ERR_R_INTERNAL_ERROR);
		return 0;
		}
	s->s3->tmp.peer_finish_md_len = i;

	return(1);
	}