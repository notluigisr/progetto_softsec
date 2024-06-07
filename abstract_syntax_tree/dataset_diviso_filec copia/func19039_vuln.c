static void check_join_failure(IRC_SERVER_REC *server, const char *channel)
{
	CHANNEL_REC *chanrec;
	char *chan2;

	if (channel[0] == '!' && channel[1] == '!')
		channel++; 

	chanrec = channel_find(SERVER(server), channel);
	if (chanrec == NULL && channel[0] == '!') {
		
		chan2 = g_strdup_printf("STR", channel+6);
		chanrec = channel_find(SERVER(server), chan2);
		g_free(chan2);
	}

	if (chanrec != NULL && !chanrec->joined) {
		chanrec->left = TRUE;
		channel_destroy(chanrec);
	}
}