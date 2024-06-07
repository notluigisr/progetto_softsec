void LanLinkProvider::dataReceived()
{
    QSslSocket* socket = qobject_cast<QSslSocket*>(sender());
    
    
    if (socket->bytesAvailable() > 8192) {
        qCWarning(KDECONNECT_CORE) << "STR" << socket->peerAddress() << socket->bytesAvailable();
        socket->disconnectFromHost();
        return;
    }

#if QT_VERSION < QT_VERSION_CHECK(5,7,0)
    if (!socket->canReadLine())
        return;
#else
    socket->startTransaction();
#endif

    const QByteArray data = socket->readLine();

    qCDebug(KDECONNECT_CORE) << "STR" << data;

    NetworkPacket* np = new NetworkPacket(QLatin1String(""));
    bool success = NetworkPacket::unserialize(data, np);

#if QT_VERSION < QT_VERSION_CHECK(5,7,0)
    if (!success) {
        delete np;
        return;
    }
#else
    if (!success) {
        delete np;
        socket->rollbackTransaction();
        return;
    }
    socket->commitTransaction();
#endif

    if (np->type() != PACKET_TYPE_IDENTITY) {
        qCWarning(KDECONNECT_CORE) << "STR" << np->type();
        delete np;
        return;
    }

    
    m_receivedIdentityPackets[socket].np = np;

    const QString& deviceId = np->get<QString>(QStringLiteral("STR"));
    

    
    disconnect(socket, &QIODevice::readyRead, this, &LanLinkProvider::dataReceived);

    if (np->get<int>(QStringLiteral("STR")) >= MIN_VERSION_WITH_SSL_SUPPORT) {

        bool isDeviceTrusted = KdeConnectConfig::instance().trustedDevices().contains(deviceId);
        configureSslSocket(socket, deviceId, isDeviceTrusted);

        qCDebug(KDECONNECT_CORE) << "STR";

        connect(socket, &QSslSocket::encrypted, this, &LanLinkProvider::encrypted);

        if (isDeviceTrusted) {
            connect(socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), this, &LanLinkProvider::sslErrors);
        }

        socket->startClientEncryption();

    } else {
        qWarning() << np->get<QString>(QStringLiteral("STR";
        
        delete m_receivedIdentityPackets.take(socket).np;
    }
}