void CoreUserInputHandler::handleOper(const BufferInfo &bufferInfo, const QString &msg)
{
    Q_UNUSED(bufferInfo)
    emit putRawLine(serverEncode(QString("STR").arg(msg)));
}