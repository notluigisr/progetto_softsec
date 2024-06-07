addStmtError(ODBCStmt *stmt, const char *SQLState, const char *errMsg, int nativeErrCode)
{
	ODBCError *error = NULL;

#ifdef ODBCDEBUG
	ODBCLOG("STR", stmt, SQLState, errMsg ? errMsg : getStandardSQLStateMsg(SQLState), nativeErrCode);
#endif
	assert(isValidStmt(stmt));

	error = newODBCError(SQLState, errMsg, nativeErrCode);
	appendODBCError(&stmt->Error, error);
}