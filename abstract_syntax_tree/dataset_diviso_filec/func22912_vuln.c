Avahi::Avahi()
{
    org::freedesktop::Avahi::Server server("STR", QDBusConnection::systemBus());
    QDBusReply<QDBusObjectPath> reply=server.ServiceBrowserNew(-1, -1, constServiceType, domainToDNS(QString()), 0);

    if (reply.isValid()) {
        service=new OrgFreedesktopAvahiServiceBrowserInterface("STR", reply.value().path(), QDBusConnection::systemBus());
        connect(service, SIGNAL(ItemNew(int,int,QString,QString,QString,uint)), SLOT(addService(int,int,QString,QString,QString,uint)));
        connect(service, SIGNAL(ItemRemove(int,int,QString,QString,QString,uint)), SLOT(removeService(int,int,QString,QString,QString,uint)));
    }
}