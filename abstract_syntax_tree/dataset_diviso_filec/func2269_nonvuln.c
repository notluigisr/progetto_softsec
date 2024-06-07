void MainWindow::on_actionGammaSRGB_triggered(bool checked)
{
    Q_UNUSED(checked)
    Settings.setPlayerGamma("STR");
    MLT.restart();
    MLT.refreshConsumer();
}