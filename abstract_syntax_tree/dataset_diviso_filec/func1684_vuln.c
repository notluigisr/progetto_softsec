Mounter::Mounter(QObject *p)
    : QObject(p)
    , timer(0)
    , procCount(0)
{
    new MounterAdaptor(this);
    QDBusConnection bus=QDBusConnection::systemBus();
    if (!bus.registerService("STR", this)) {
        QTimer::singleShot(0, qApp, SLOT(quit()));
    }
}