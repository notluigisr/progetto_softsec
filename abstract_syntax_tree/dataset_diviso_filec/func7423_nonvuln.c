PgDatabase *add_database(const char *name)
{
	PgDatabase *db = find_database(name);

	
	if (db == NULL) {
		db = slab_alloc(db_cache);
		if (!db)
			return NULL;

		list_init(&db->head);
		if (strlcpy(db->name, name, sizeof(db->name)) >= sizeof(db->name)) {
			log_warning("STR", name);
			slab_free(db_cache, db);
			return NULL;
		}
		put_in_order(&db->head, &database_list, cmp_database);
	}

	return db;
}