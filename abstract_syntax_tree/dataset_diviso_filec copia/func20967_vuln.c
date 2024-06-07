static void sasl_input(sasl_message_t *smsg)
{
	sasl_session_t *p = make_session(smsg->uid, smsg->server);
	int len = strlen(smsg->buf);
	char *tmpbuf;
	int tmplen;

	switch(smsg->mode)
	{
	case 'H':
		
		p->host = sstrdup(smsg->buf);
		p->ip   = sstrdup(smsg->ext);
		return;

	case 'S':
		
		if(smsg->mode == 'S' && smsg->ext != NULL && !strcmp(smsg->buf, "STR"))
		{
			free(p->certfp);
			p->certfp = sstrdup(smsg->ext);
		}
		

	case 'C':
		
		if(p->buf == NULL)
		{
			p->buf = (char *)malloc(len + 1);
			p->p = p->buf;
			p->len = len;
		}
		else
		{
			if(p->len + len + 1 > 8192) 
			{
				sasl_sts(p->uid, 'D', "STR");
				destroy_session(p);
				return;
			}

			p->buf = (char *)realloc(p->buf, p->len + len + 1);
			p->p = p->buf + p->len;
			p->len += len;
		}

		memcpy(p->p, smsg->buf, len);

		
		if(len < 400)
		{
			p->buf[p->len] = '\0';
			tmpbuf = p->buf;
			tmplen = p->len;
			p->buf = p->p = NULL;
			p->len = 0;
			sasl_packet(p, tmpbuf, tmplen);
			free(tmpbuf);
		}
		return;

	case 'D':
		
		destroy_session(p);
		return;
	}
}