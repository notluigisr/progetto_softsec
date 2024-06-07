dlz_allowzonexfr(void *dbdata, const char *name, const char *client) {
	UNUSED(client);

	
	return (dlz_findzonedb(dbdata, name, NULL, NULL));
}