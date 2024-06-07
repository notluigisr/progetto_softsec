bool PostgreSqlStorage::logMessage(Message &msg)
{
    QSqlDatabase db = logDb();
    if (!db.transaction()) {
        qWarning() << "STR";
        qWarning() << "STR" << qPrintable(db.lastError().text());
        return false;
    }

    QSqlQuery getSenderIdQuery = executePreparedQuery("STR", msg.sender(), db);
    int senderId;
    if (getSenderIdQuery.first()) {
        senderId = getSenderIdQuery.value(0).toInt();
    }
    else {
        
        
        savePoint("STR", db);
        QSqlQuery addSenderQuery = executePreparedQuery("STR", msg.sender(), db);

        if (addSenderQuery.lastError().isValid()) {
            rollbackSavePoint("STR", db);
            getSenderIdQuery = db.exec(getSenderIdQuery.lastQuery());
            getSenderIdQuery.first();
            senderId = getSenderIdQuery.value(0).toInt();
        }
        else {
            releaseSavePoint("STR", db);
            addSenderQuery.first();
            senderId = addSenderQuery.value(0).toInt();
        }
    }

    QVariantList params;
    params << msg.timestamp()
           << msg.bufferInfo().bufferId().toInt()
           << msg.type()
           << (int)msg.flags()
           << senderId
           << msg.contents();
    QSqlQuery logMessageQuery = executePreparedQuery("STR", params, db);

    if (!watchQuery(logMessageQuery)) {
        db.rollback();
        return false;
    }

    logMessageQuery.first();
    MsgId msgId = logMessageQuery.value(0).toInt();
    db.commit();
    if (msgId.isValid()) {
        msg.setMsgId(msgId);
        return true;
    }
    else {
        return false;
    }
}