void CoreUserInputHandler::handleCtcp(const BufferInfo &bufferInfo, const QString &msg)
{
    Q_UNUSED(bufferInfo)

    QString nick = msg.section(' ', 0, 0);
    QString ctcpTag = msg.section(' ', 1, 1).toUpper();
    if (ctcpTag.isEmpty())
        return;

    QString message = msg.section(' ', 2);
    QString verboseMessage = tr("STR").arg(ctcpTag).arg(nick);

    if (ctcpTag == "STR") {
        message = QString::number(QDateTime::currentMSecsSinceEpoch());
    }

    
    coreNetwork()->coreSession()->ctcpParser()->query(coreNetwork(), nick, ctcpTag, message);
    emit displayMsg(Message::Action, BufferInfo::StatusBuffer, "", verboseMessage, network()->myNick());
}