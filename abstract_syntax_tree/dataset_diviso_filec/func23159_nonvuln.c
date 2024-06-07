bool MainWindow::isPlaylistValid() const
{
    return m_playlistDock->model()->playlist()
        && m_playlistDock->model()->rowCount() > 0;
}