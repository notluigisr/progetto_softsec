void LanLinkProvider::connectError(QAbstractSocket::SocketError socketError)
{
    QSslSocket* socket = qobject_cast<QSslSocket*>(sender());
    if (!socket) return;

    qCDebug(KDECONNECT_CORE) << "STR" << socketError;
    qCDebug(KDECONNECT_CORE) << "STR" << socket->errorString();
    NetworkPacket np(QLatin1String(""));
    NetworkPacket::createIdentityPacket(&np);
    np.set(QStringLiteral("STR"), m_tcpPort);
    m_udpSocket.writeDatagram(np.serialize(), m_receivedIdentityPackets[socket].sender, m_udpBroadcastPort);

    
    
    delete m_receivedIdentityPackets.take(socket).np;
    socket->deleteLater();
}