ns_client_newnamebuf(ns_client_t *client) {
	isc_buffer_t *dbuf = NULL;

	CTRACE("STR");

	isc_buffer_allocate(client->mctx, &dbuf, 1024);
	ISC_LIST_APPEND(client->query.namebufs, dbuf, link);

	CTRACE("STR");
	return (ISC_R_SUCCESS);
}