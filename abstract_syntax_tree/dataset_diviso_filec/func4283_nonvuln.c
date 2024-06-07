CHAT_DCC_REC *dcc_chat_find_id(const char *id)
{
	GSList *tmp;

	g_return_val_if_fail(id != NULL, NULL);

	for (tmp = dcc_conns; tmp != NULL; tmp = tmp->next) {
		CHAT_DCC_REC *dcc = tmp->data;

		if (IS_DCC_CHAT(dcc) && dcc->id != NULL &&
		    g_ascii_strcasecmp(dcc->id, id) == 0)
			return dcc;
	}

	return NULL;
}