void MainWindow::onPlayerTabIndexChanged(int index)
{
    if (Player::SourceTabIndex == index)
        m_timelineDock->saveAndClearSelection();
    else
        m_timelineDock->restoreSelection();
}