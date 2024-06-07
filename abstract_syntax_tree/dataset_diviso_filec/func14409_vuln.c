void MainWindow::on_actionUpgrade_triggered()
{
    if (Settings.askUpgradeAutmatic()) {
        QMessageBox dialog(QMessageBox::Question,
           qApp->applicationName(),
           tr("STR"),
           QMessageBox::No |
           QMessageBox::Yes,
           this);
        dialog.setWindowModality(QmlApplication::dialogModality());
        dialog.setDefaultButton(QMessageBox::Yes);
        dialog.setEscapeButton(QMessageBox::No);
        dialog.setCheckBox(new QCheckBox(tr("STR")));
        Settings.setCheckUpgradeAutomatic(dialog.exec() == QMessageBox::Yes);
        if (dialog.checkBox()->isChecked())
            Settings.setAskUpgradeAutomatic(false);
    }
    showStatusMessage("STR");
    m_network.get(QNetworkRequest(QUrl("STR")));
}