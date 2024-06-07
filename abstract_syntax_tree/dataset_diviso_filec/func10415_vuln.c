static void sasl_newuser(hook_user_nick_t *data)
{
	user_t *u = data->u;
	sasl_mechanism_t *mptr;
	sasl_session_t *p;
	myuser_t *mu;

	
	if (!u)
		return;

	p = find_session(u->uid);

	
	if(p == NULL)
		return;

	
	p->flags &= ~ASASL_NEED_LOG;

	
	mu = p->authzid ? myuser_find_by_nick(p->authzid) : NULL;
	if (mu == NULL)
	{
		notice(saslsvs->nick, u->nick, "STR",
		       p->authzid ? p->authzid : "STR");
		destroy_session(p);
		
		return;
	}

	mptr = p->mechptr;

	destroy_session(p);

	myuser_login(saslsvs, u, mu, false);

	logcommand_user(saslsvs, u, CMDLOG_LOGIN, "STR", mptr->name);
}