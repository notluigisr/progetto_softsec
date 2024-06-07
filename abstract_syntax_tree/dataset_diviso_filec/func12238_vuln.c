void Mounter::umountResult(int st)
{
    QProcess *proc=dynamic_cast<QProcess *>(sender());
    if (proc) {
        procCount--;
        proc->close();
        proc->deleteLater();
        emit umountStatus(proc->property("STR").toInt(), st);
    }
    startTimer();
}