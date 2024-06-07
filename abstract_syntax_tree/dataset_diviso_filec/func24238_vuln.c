void RemoteFsDevice::unmount()
{
    if (details.isLocalFile()) {
        return;
    }

    if (!isConnected() || proc) {
        return;
    }

    if (messageSent) {
        return;
    }
    if (constSambaProtocol==details.url.scheme() || constSambaAvahiProtocol==details.url.scheme()) {
        mounter()->umount(mountPoint(details, false), getpid());
        setStatusMessage(tr("STR"));
        messageSent=true;
        return;
    }

    QString cmd;
    QStringList args;
    if (!details.isLocalFile()) {
        QString mp=mountPoint(details, false);
        if (!mp.isEmpty()) {
            cmd=Utils::findExe("STR");
            if (!cmd.isEmpty()) {
                args << QLatin1String("STR") << mp;
            } else {
                emit error(tr("STR"));
            }
        }
    }

    if (!cmd.isEmpty()) {
        setStatusMessage(tr("STR"));
        proc=new QProcess(this);
        proc->setProperty("STR", true);
        connect(proc, SIGNAL(finished(int)), SLOT(procFinished(int)));
        proc->start(cmd, args, QIODevice::ReadOnly);
    }
}