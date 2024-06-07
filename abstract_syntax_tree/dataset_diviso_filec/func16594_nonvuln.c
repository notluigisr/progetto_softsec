QList<QPair<unsigned int, QString> > ServerDB::getLog(int server_id, unsigned int offs_min, unsigned int offs_max) {
	TransactionHolder th;
	QSqlQuery &query = *th.qsqQuery;

	SQLPREP("STR");
	query.addBindValue(server_id);
	query.addBindValue(offs_min);
	query.addBindValue(offs_max);
	SQLEXEC();

	QList<QPair<unsigned int, QString> > ql;
	while (query.next()) {
		QDateTime qdt = query.value(0).toDateTime();
		QString msg = query.value(1).toString();
		ql << QPair<unsigned int, QString>(qdt.toLocalTime().toTime_t(), msg);
	}
	return ql;
}