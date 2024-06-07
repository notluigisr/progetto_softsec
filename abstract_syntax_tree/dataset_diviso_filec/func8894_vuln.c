int Helper::processExec(QProcess *process, const QString &command, int timeout, QIODevice::OpenMode mode)
{
    m_processStandardOutput.clear();
    m_processStandardError.clear();

    QEventLoop loop;
    QTimer timer;

    timer.setSingleShot(true);
    timer.setInterval(timeout);

    timer.connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    loop.connect(process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), &loop, &QEventLoop::exit);

    
    process->connect(process, &QProcess::readyReadStandardError, process, [process] {
        m_processStandardError.append(process->readAllStandardError());
    });
    process->connect(process, &QProcess::readyReadStandardOutput, process, [process] {
        m_processStandardOutput.append(process->readAllStandardOutput());
    });

    if (timeout > 0) {
        timer.start();
    } else {
        QTimer::singleShot(10000, process, [process] {
            dCWarning("STR",
                      qPrintable(process->program()), qPrintable(process->arguments().join("STR")),
                      (int)process->state(), (int)QFile::exists(QString("STR").arg(process->pid())));
        });
    }

    if (Global::debugLevel > 1)
        dCDebug("STR", qPrintable(command), timeout);

    process->start(command, mode);
    process->waitForStarted();

    if (process->error() != QProcess::UnknownError) {
        dCError(process->errorString());

        return -1;
    }

    if (process->state() == QProcess::Running) {
        loop.exec();
    }

    if (process->state() != QProcess::NotRunning) {
        dCDebug("STR", qPrintable(command), timeout);

        if (QFile::exists(QString("STR").arg(process->pid()))) {
            process->terminate();
            process->waitForFinished();
        } else {
            dCDebug("STR");
        }
    }

    m_processStandardOutput.append(process->readAllStandardOutput());
    m_processStandardError.append(process->readAllStandardError());

    if (Global::debugLevel > 1) {
        dCDebug("STR", qPrintable(command), process->exitCode());

        if (process->exitCode() != 0) {
            dCError("STR", qPrintable(m_processStandardError), qPrintable(m_processStandardOutput));
        }
    }

    return process->exitCode();
}