void MainWindow::onPlaylistOutChanged(int out)
{
    m_player->blockSignals(true);
    m_player->setOut(out);
    m_player->blockSignals(false);
}