int ldb_handler_fold(struct ldb_context *ldb, void *mem_ctx,
			    const struct ldb_val *in, struct ldb_val *out)
{
	char *s, *t;
	size_t l;

	if (!in || !out || !(in->data)) {
		return -1;
	}

	out->data = (uint8_t *)ldb_casefold(ldb, mem_ctx, (const char *)(in->data), in->length);
	if (out->data == NULL) {
		ldb_debug(ldb, LDB_DEBUG_ERROR, "STR", (int)in->length, (const char *)in->data);
		return -1;
	}

	s = (char *)(out->data);
	
	
	l = strlen(s);
	while (l > 0 && s[l - 1] == ' ') l--;
	s[l] = '\0';
	
	
	if (*s == ' ') {
		for (t = s; *s == ' '; s++) ;

		
		memmove(t, s, l);

		s = t;
	}

	
	while ((t = strchr(s, ' ')) != NULL) {
		for (s = t; *s == ' '; s++) ;

		if ((s - t) > 1) {
			l = strlen(s);

			
			memmove(t + 1, s, l);
		}
	}

	out->length = strlen((char *)out->data);
	return 0;
}