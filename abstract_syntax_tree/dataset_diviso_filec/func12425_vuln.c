destroyODBCStmt(ODBCStmt *stmt)
{
	ODBCStmt **stmtp;

	assert(isValidStmt(stmt));

	
	stmt->Type = 0;

	
	assert(stmt->Dbc);
	assert(stmt->Dbc->FirstStmt);

	
	stmtp = &stmt->Dbc->FirstStmt;

	while (*stmtp && *stmtp != stmt)
		stmtp = &(*stmtp)->next;
	

	assert(*stmtp == stmt);	

	
	*stmtp = stmt->next;

	
	deleteODBCErrorList(&stmt->Error);

	destroyODBCDesc(stmt->ImplParamDescr);
	destroyODBCDesc(stmt->ImplRowDescr);
	destroyODBCDesc(stmt->AutoApplParamDescr);
	destroyODBCDesc(stmt->AutoApplRowDescr);

	if (stmt->hdl)
		mapi_close_handle(stmt->hdl);

	free(stmt);
}