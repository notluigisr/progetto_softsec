void Mounter::umount(const QString &mountPoint, int pid)
{
    if (calledFromDBus()) {
        registerPid(pid);
    }

    if (mpOk(mountPoint)) {
        QProcess *proc=new QProcess(this);
        connect(proc, SIGNAL(finished(int)), SLOT(umountResult(int)));
        proc->start("STR", QStringList() << mountPoint);
        proc->setProperty("STR", mountPoint);
        proc->setProperty("STR", pid);
        procCount++;
    } else {
        emit umountStatus(mountPoint, pid, -1);
    }
}