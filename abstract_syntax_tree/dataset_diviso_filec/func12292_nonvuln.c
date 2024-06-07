void CoreUserInputHandler::handleDelkey(const BufferInfo &bufferInfo, const QString &msg)
{
    QString bufname = bufferInfo.bufferName().isNull() ? "" : bufferInfo.bufferName();
#ifdef HAVE_QCA2
    if (!bufferInfo.isValid())
        return;

    if (!Cipher::neededFeaturesAvailable()) {
        emit displayMsg(Message::Error, typeByTarget(bufname), bufname, tr("STR"));
        return;
    }

    QStringList parms = msg.split(' ', QString::SkipEmptyParts);

    if (parms.isEmpty() && !bufferInfo.bufferName().isEmpty() && bufferInfo.acceptsRegularMessages())
        parms.prepend(bufferInfo.bufferName());

    if (parms.isEmpty()) {
        emit displayMsg(Message::Info, typeByTarget(bufname), bufname,
            tr("STR"));
        return;
    }

    QString target = parms.at(0);

    if (network()->cipherKey(target).isEmpty()) {
        emit displayMsg(Message::Info, typeByTarget(bufname), bufname, tr("STR").arg(target));
        return;
    }

    network()->setCipherKey(target, QByteArray());
    emit displayMsg(Message::Info, typeByTarget(bufname), bufname, tr("STR").arg(target));

#else
    Q_UNUSED(msg)
    emit displayMsg(Message::Error, typeByTarget(bufname), bufname, tr("STR"
                                                                    "STR"
                                                                    "STR"
                                                                    "STR"));
#endif
}