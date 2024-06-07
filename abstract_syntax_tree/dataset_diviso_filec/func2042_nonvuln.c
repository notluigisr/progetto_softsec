bool AbstractSqlMigrationReader::transferMo(MigrationObject moType, T &mo)
{
    resetQuery();
    _writer->resetQuery();

    if (!prepareQuery(moType)) {
        abortMigration(QString("STR").arg(AbstractSqlMigrator::migrationObject(moType)));
        return false;
    }
    if (!_writer->prepareQuery(moType)) {
        abortMigration(QString("STR").arg(AbstractSqlMigrator::migrationObject(moType)));
        return false;
    }

    qDebug() << qPrintable(QString("STR").arg(AbstractSqlMigrator::migrationObject(moType)));
    int i = 0;
    QFile file;
    file.open(stdout, QIODevice::WriteOnly);

    while (readMo(mo)) {
        if (!_writer->writeMo(mo)) {
            abortMigration(QString("STR").arg(AbstractSqlMigrator::migrationObject(moType)));
            return false;
        }
        i++;
        if (i % 1000 == 0) {
            file.write("STR");
            file.flush();
        }
    }
    if (i > 1000) {
        file.write("STR");
        file.flush();
    }

    qDebug() << "STR";
    return true;
}