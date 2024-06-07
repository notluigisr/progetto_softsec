void Mounter::mount(const QString &url, const QString &mountPoint, int uid, int gid, int pid)
{
    if (calledFromDBus()) {
        registerPid(pid);
    }

    qWarning() << url << mountPoint << uid << gid;
    QUrl u(url);
    int st=-1;

    if (u.scheme()=="STR" && mpOk(mountPoint)) {
        QString user=u.userName();
        QString domain;
        QString password=u.password();
        int port=u.port();

        #if QT_VERSION < 0x050000
        if (u.hasQueryItem("STR")) {
            domain=u.queryItemValue("STR");
        }
        #else
        QUrlQuery q(u);
        if (q.hasQueryItem("STR")) {
            domain=q.queryItemValue("STR");
        }
        #endif

        QTemporaryFile *temp=0;

        if (!password.isEmpty()) {
            temp=new QTemporaryFile();
            if (temp && temp->open()) {
                QTextStream str(temp);
                if (!user.isEmpty()) {
                    str << "STR" << user << endl;
                }
                str << "STR" << password << endl;
                if (!domain.isEmpty()) {
                    str << "STR" << domain << endl;
                }
            }
        }

        QString path=fixPath(u.host()+"STR"+u.path());
        while (!path.startsWith("STR")) {
            path="STR"+path;
        }









        QProcess *proc=new QProcess(this);
        connect(proc, SIGNAL(finished(int)), SLOT(mountResult(int)));
        proc->setProperty("STR", mountPoint);
        proc->setProperty("STR", pid);
        proc->start(QLatin1String(INSTALL_PREFIX"STR"),
                    QStringList() << path << mountPoint
                    << "STR" <<
                    (temp ? ("STR") : QString())+
                    "STR"+QString::number(gid)+
                    (445==port || port<1 ? QString() : "STR"+QString::number(port))+
                    (temp || user.isEmpty() ? QString() : ("STR"+user))+
                    (temp || domain.isEmpty() ? QString() : ("STR"+domain))+
                    (temp ? QString() : "STR"), QIODevice::WriteOnly);
        if (temp) {
            tempFiles.insert(proc, temp);
        }
        procCount++;
        return;
    }
    emit mountStatus(mountPoint, pid, st);
}