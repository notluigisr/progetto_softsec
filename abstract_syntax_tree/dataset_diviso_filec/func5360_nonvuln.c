void MainWindow::showStatusMessage(const QString& message, int timeoutSeconds)
{
    LOG_INFO() << message;
    m_player->setStatusLabel(message, timeoutSeconds, 0 );
    m_statusBarAction.reset();
}