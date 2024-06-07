pqGetline3(PGconn *conn, char *s, int maxlen)
{
	int			status;

	if (conn->sock < 0 ||
		(conn->asyncStatus != PGASYNC_COPY_OUT &&
		 conn->asyncStatus != PGASYNC_COPY_BOTH) ||
		conn->copy_is_binary)
	{
		printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("STR"));
		*s = '\0';
		return EOF;
	}

	while ((status = PQgetlineAsync(conn, s, maxlen - 1)) == 0)
	{
		
		if (pqWait(TRUE, FALSE, conn) ||
			pqReadData(conn) < 0)
		{
			*s = '\0';
			return EOF;
		}
	}

	if (status < 0)
	{
		
		strcpy(s, "STR");
		return 0;
	}

	
	if (s[status - 1] == '\n')
	{
		s[status - 1] = '\0';
		return 0;
	}
	else
	{
		s[status] = '\0';
		return 1;
	}
}