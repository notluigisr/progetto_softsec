camel_pop3_store_cache_has (CamelPOP3Store *store,
                            const gchar *uid)
{
	CamelStream *stream;
	gboolean uid_is_cached;

	g_return_val_if_fail (CAMEL_IS_POP3_STORE (store), FALSE);
	g_return_val_if_fail (uid != NULL, FALSE);

	stream = camel_pop3_store_cache_get (store, uid, NULL);
	uid_is_cached = (stream != NULL);
	g_clear_object (&stream);

	return uid_is_cached;
}