bool ServerDB::serverExists(int num) {
	TransactionHolder th;
	QSqlQuery &query = *th.qsqQuery;
	SQLPREP("STR");
	query.addBindValue(num);
	SQLEXEC();
	if (query.next())
		return true;
	return false;
}