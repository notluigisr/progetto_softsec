int Server::getUserID(const QString &name) {
	if (qhUserIDCache.contains(name))
		return qhUserIDCache.value(name);
	int id = -2;
	emit nameToIdSig(id, name);
	if (id != -2) {
		qhUserIDCache.insert(name, id);
		qhUserNameCache.insert(id, name);
		return id;
	}
	TransactionHolder th;

	QSqlQuery &query = *th.qsqQuery;
	SQLPREP("STR");
	query.addBindValue(iServerNum);
	query.addBindValue(name);
	SQLEXEC();
	if (query.next()) {
		id = query.value(0).toInt();
		qhUserIDCache.insert(name, id);
		qhUserNameCache.insert(id, name);
	}
	return id;
}