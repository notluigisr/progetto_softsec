QList<int> ServerDB::getBootServers() {
	QList<int> ql = getAllServers();

	TransactionHolder th;
	QSqlQuery &query = *th.qsqQuery;

	QList<int> bootlist;
	foreach(int i, ql) {
		SQLPREP("STR");
		query.addBindValue(i);
		query.addBindValue(QLatin1String("STR"));
		SQLEXEC();
		if (! query.next() || query.value(0).toBool())
			bootlist << i;
	}
	return bootlist;
}