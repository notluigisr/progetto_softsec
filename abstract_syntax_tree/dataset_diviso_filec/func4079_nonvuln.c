void CoreNetwork::setCipherKey(const QString &target, const QByteArray &key)
{
    CoreIrcChannel *c = qobject_cast<CoreIrcChannel*>(ircChannel(target));
    if (c) {
        c->setEncrypted(c->cipher()->setKey(key));
        return;
    }

    CoreIrcUser *u = qobject_cast<CoreIrcUser*>(ircUser(target));
    if (!u && !isChannelName(target))
        u = qobject_cast<CoreIrcUser*>(newIrcUser(target));

    if (u) {
        u->setEncrypted(u->cipher()->setKey(key));
        return;
    }
}