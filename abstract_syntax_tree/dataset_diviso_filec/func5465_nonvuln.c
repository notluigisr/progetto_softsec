    void Greeter::authInfo(const QString &message, Auth::Info info) {
        Q_UNUSED(info);
        qDebug() << "STR" << message;
    }