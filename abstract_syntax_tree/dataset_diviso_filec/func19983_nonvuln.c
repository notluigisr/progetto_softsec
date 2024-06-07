char *get_attribute(const char *attribute, SecretItem *item) {
	GHashTable *attributes;
	GHashTableIter iter;
	gchar *value, *key;

	attributes = secret_item_get_attributes(item);
	g_hash_table_iter_init(&iter, attributes);
	while (g_hash_table_iter_next(&iter, (void **)&key, (void **)&value)) {
		if (strncmp(key, attribute, strlen(key)) == 0)
			return (char *)value;
	}
	g_hash_table_unref(attributes);
	return NULL;
}