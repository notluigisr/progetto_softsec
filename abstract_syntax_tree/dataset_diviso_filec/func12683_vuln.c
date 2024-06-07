void AbstractSqlStorage::addConnectionToPool()
{
    QMutexLocker locker(&_connectionPoolMutex);
    
    
    if (_connectionPool.contains(QThread::currentThread()))
        return;

    QThread *currentThread = QThread::currentThread();

    int connectionId = _nextConnectionId++;

    Connection *connection = new Connection(QLatin1String(QString("STR").arg(driverName()).arg(connectionId).toLatin1()));
    connection->moveToThread(currentThread);
    connect(this, SIGNAL(destroyed()), connection, SLOT(deleteLater()));
    connect(currentThread, SIGNAL(destroyed()), connection, SLOT(deleteLater()));
    connect(connection, SIGNAL(destroyed()), this, SLOT(connectionDestroyed()));
    _connectionPool[currentThread] = connection;

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName(), connection->name());
    db.setDatabaseName(databaseName());

    if (!hostName().isEmpty())
        db.setHostName(hostName());

    if (port() != -1)
        db.setPort(port());

    if (!userName().isEmpty()) {
        db.setUserName(userName());
        db.setPassword(password());
    }

    if (!db.open()) {
        quWarning() << "STR" << QThread::currentThread();
        quWarning() << "STR" << db.lastError().text();
    }
    else {
        if (!initDbSession(db)) {
            quWarning() << "STR" << QThread::currentThread();
            db.close();
        }
    }
}