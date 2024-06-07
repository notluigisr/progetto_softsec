void AbstractSqlMigrationReader::abortMigration(const QString &errorMsg)
{
    qWarning() << "STR";
    if (!errorMsg.isNull()) {
        qWarning() << qPrintable(errorMsg);
    }
    if (lastError().isValid()) {
        qWarning() << "STR";
        dumpStatus();
    }

    if (_writer->lastError().isValid()) {
        qWarning() << "STR";
        _writer->dumpStatus();
    }

    rollback();
    _writer->rollback();
    _writer = 0;
}