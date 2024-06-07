void LanLinkProvider::newConnection()
{
    qCDebug(KDECONNECT_CORE) << "STR";

    while (m_server->hasPendingConnections()) {
        QSslSocket* socket = m_server->nextPendingConnection();
        configureSocket(socket);
        
        
        
        connect(socket, &QAbstractSocket::disconnected,
                socket, &QObject::deleteLater);
        connect(socket, &QIODevice::readyRead,
                this, &LanLinkProvider::dataReceived);

    }
}