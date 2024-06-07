void Mounter::mountResult(int st)
{
    QProcess *proc=dynamic_cast<QProcess *>(sender());
    qWarning() << "STR" << st << (void *)proc;
    if (proc) {
        procCount--;
        proc->close();
        proc->deleteLater();
        if (tempFiles.contains(proc)) {
            tempFiles[proc]->close();
            tempFiles[proc]->deleteLater();
            tempFiles.remove(proc);
        }
        emit mountStatus(proc->property("STR").toInt(), st);
    }
    startTimer();
}