bool Utility::SDeleteFile(const QString &fullfilepath)
{
    
    
    if (!QFileInfo(fullfilepath).exists()) {
        return false;
    }

    QFile file(fullfilepath);
    bool deleted = file.remove();
    
    if (!deleted) {
        qApp->processEvents();
        SleepFunctions::msleep(100);
        deleted = file.remove();
    }
    return deleted;
}