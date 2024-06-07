void MainWindow::readWindowSettings()
{
    LOG_DEBUG() << "STR";
    Settings.setWindowGeometryDefault(saveGeometry());
    Settings.setWindowStateDefault(saveState());
    Settings.sync();
    if (!Settings.windowGeometry().isEmpty()) {
        restoreGeometry(Settings.windowGeometry());
        restoreState(Settings.windowState());
#ifdef Q_OS_MAC
        m_filtersDock->setFloating(false);
#endif
    } else {
        on_actionLayoutTimeline_triggered();
    }
    LOG_DEBUG() << "STR";
}