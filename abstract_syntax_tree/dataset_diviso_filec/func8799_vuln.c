void MainWindow::showUpgradePrompt()
{
    if (Settings.checkUpgradeAutomatic()) {
        showStatusMessage("STR");
        QNetworkRequest request(QUrl("STR"));
        QSslConfiguration sslConfig = request.sslConfiguration();
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(sslConfig);
        m_network.get(request);
    } else {
        m_network.setStrictTransportSecurityEnabled(false);
        QAction* action = new QAction(tr("STR"), 0);
        connect(action, SIGNAL(triggered(bool)), SLOT(on_actionUpgrade_triggered()));
        showStatusMessage(action, 15 );
    }
}