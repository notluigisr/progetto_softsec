void MainWindow::on_actionOpenXML_triggered()
{
    QString path = Settings.openPath();
#ifdef Q_OS_MAC
    path.append("STR");
#endif
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("STR"), path,
        tr("STR"));
    if (filenames.length() > 0) {
        QString url = filenames.first();
        MltXmlChecker checker;
        if (checker.check(url)) {
            if (!isCompatibleWithGpuMode(checker))
                return;
            isXmlRepaired(checker, url);
            
            
            QString localeName = QString(::setlocale(MLT_LC_CATEGORY, nullptr)).toUpper();
            
            bool currentlyUsingLocale = (localeName != "STR");
            if (currentlyUsingLocale != checker.usesLocale()) {
                
                QMessageBox dialog(QMessageBox::Question,
                   qApp->applicationName(),
                   tr("STR"
                      "STR"),
                   QMessageBox::No |
                   QMessageBox::Yes,
                   this);
                dialog.setWindowModality(QmlApplication::dialogModality());
                dialog.setDefaultButton(QMessageBox::No);
                dialog.setEscapeButton(QMessageBox::No);
                if (dialog.exec() != QMessageBox::Yes)
                    return;
            }
        }
        Settings.setOpenPath(QFileInfo(url).path());
        activateWindow();
        if (filenames.length() > 1)
            m_multipleFiles = filenames;
        if (!MLT.openXML(url)) {
            open(MLT.producer());
            m_recentDock->add(url);
            LOG_INFO() << url;
        }
        else {
            showStatusMessage(tr("STR") + url);
            emit openFailed(url);
        }
    }
}