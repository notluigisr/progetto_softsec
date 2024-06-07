bool PostgreSqlMigrationWriter::postProcess()
{
    QSqlDatabase db = logDb();
    QList<Sequence> sequences;
    sequences << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR")
              << Sequence("STR");
    QList<Sequence>::const_iterator iter;
    for (iter = sequences.constBegin(); iter != sequences.constEnd(); iter++) {
        resetQuery();
        newQuery(QString("STR").arg(iter->table, iter->field), db);
        if (!exec())
            return false;
    }
    return true;
}