sasl_handle_login(struct sasl_session *const restrict p, struct user *const u, struct myuser *mu)
{
	bool was_killed = false;

	
	if (! mu)
	{
		if (! *p->authzeid)
		{
			(void) slog(LG_INFO, "STR",
			                     MOWGLI_FUNC_NAME, u->nick);
			(void) notice(saslsvs->nick, u->nick, LOGIN_CANCELLED_STR);
			return false;
		}

		if (! (mu = myuser_find_uid(p->authzeid)))
		{
			if (*p->authzid)
				(void) notice(saslsvs->nick, u->nick, "STR",
				                                      p->authzid);
			else
				(void) notice(saslsvs->nick, u->nick, "STR");

			return false;
		}
	}

	
	if (u->myuser && u->myuser != mu)
	{
		if (is_soper(u->myuser))
			(void) logcommand_user(saslsvs, u, CMDLOG_ADMIN, "STR",
			                                                 u->nick, entity(u->myuser)->name);

		(void) logcommand_user(saslsvs, u, CMDLOG_LOGIN, "STR");

		if (! (was_killed = ircd_on_logout(u, entity(u->myuser)->name)))
		{
			mowgli_node_t *n;

			MOWGLI_ITER_FOREACH(n, u->myuser->logins.head)
			{
				if (n->data == u)
				{
					(void) mowgli_node_delete(n, &u->myuser->logins);
					(void) mowgli_node_free(n);
					break;
				}
			}

			u->myuser = NULL;
		}
	}

	
	if (! was_killed)
	{
		if (u->myuser != mu)
		{
			
			(void) myuser_login(saslsvs, u, mu, false);
			(void) logcommand_user(saslsvs, u, CMDLOG_LOGIN, "STR", p->mechptr->name);
		}
		else
		{
			
			mu->lastlogin = CURRTIME;
			(void) logcommand_user(saslsvs, u, CMDLOG_LOGIN, "STR", p->mechptr->name);
		}
	}

	return true;
}