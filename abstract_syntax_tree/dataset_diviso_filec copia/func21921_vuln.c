int tls1_enc(SSL *s, int send)
	{
	SSL3_RECORD *rec;
	EVP_CIPHER_CTX *ds;
	unsigned long l;
	int bs,i,j,k,pad=0,ret,mac_size=0;
	const EVP_CIPHER *enc;

	if (send)
		{
		ds=s->enc_write_ctx;
		rec= &(s->s3->wrec);
		if (s->enc_write_ctx == NULL)
			enc=NULL;
		else
			enc=EVP_CIPHER_CTX_cipher(s->enc_write_ctx);
		}
	else
		{
		ds=s->enc_read_ctx;
		rec= &(s->s3->rrec);
		if (s->enc_read_ctx == NULL)
			enc=NULL;
		else
			enc=EVP_CIPHER_CTX_cipher(s->enc_read_ctx);
		}

#ifdef KSSL_DEBUG
	printf("STR", send);
#endif    

	if ((s->session == NULL) || (ds == NULL) || (enc == NULL))
		{
		memmove(rec->data,rec->input,rec->length);
		rec->input=rec->data;
		ret = 1;
		}
	else
		{
		l=rec->length;
		bs=EVP_CIPHER_block_size(ds->cipher);

		if ((bs != 1) && send)
			{
			i=bs-((int)l%bs);

			

			
			j=i-1;
			if (s->options & SSL_OP_TLS_BLOCK_PADDING_BUG)
				{
				if (s->s3->flags & TLS1_FLAGS_TLS_PADDING_BUG)
					j++;
				}
			for (k=(int)l; k<(int)(l+i); k++)
				rec->input[k]=j;
			l+=i;
			rec->length+=i;
			}

#ifdef KSSL_DEBUG
		{
		unsigned long ui;
		printf("STR",
			ds,rec->data,rec->input,l);
		printf("STR",
			ds->buf_len, ds->cipher->key_len,
			DES_KEY_SZ, DES_SCHEDULE_SZ,
			ds->cipher->iv_len);
		printf("STR");
		for (i=0; i<ds->cipher->iv_len; i++) printf("STR", ds->iv[i]);
		printf("STR");
		printf("STR");
		for (ui=0; ui<l; ui++) printf("STR", rec->input[ui]);
		printf("STR");
		}
#endif	

		if (!send)
			{
			if (l == 0 || l%bs != 0)
				{
				SSLerr(SSL_F_TLS1_ENC,SSL_R_BLOCK_CIPHER_PAD_IS_WRONG);
				ssl3_send_alert(s,SSL3_AL_FATAL,SSL_AD_DECRYPTION_FAILED);
				return 0;
				}
			}
		
		EVP_Cipher(ds,rec->data,rec->input,l);

#ifdef KSSL_DEBUG
		{
                unsigned long ki;
                printf("STR");
		for (ki=0; ki<l; i++)
                        printf("STR");
                }
#endif	

		rec->orig_len = rec->length;

		ret = 1;
		if (s->read_hash != NULL)
			mac_size = EVP_MD_size(s->read_hash);
		if ((bs != 1) && !send)
			ret = tls1_cbc_remove_padding(s, rec, bs, mac_size);
		if (pad && !send)
			rec->length -= pad;
		}
	return ret;
	}