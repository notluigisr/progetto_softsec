SMBC_remove_unused_server(SMBCCTX * context,
                          SMBCSRV * srv)
{
	SMBCFILE * file;

	
	if (!context || !context->internal->initialized || !srv) {
                return 1;
        }

	
	for (file = context->internal->files; file; file = file->next) {
		if (file->srv == srv) {
			
			DEBUG(3, ("STR"
                                  "STR",
				  srv, file));
			return 1;
		}
	}

	DLIST_REMOVE(context->internal->servers, srv);

	cli_shutdown(srv->cli);
	srv->cli = NULL;

	DEBUG(3, ("STR", srv));

	smbc_getFunctionRemoveCachedServer(context)(context, srv);

        SAFE_FREE(srv);
	return 0;
}