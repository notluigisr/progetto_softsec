QVariant Server::getConf(const QString &key, QVariant def) {
	return ServerDB::getConf(iServerNum, key, def);
}