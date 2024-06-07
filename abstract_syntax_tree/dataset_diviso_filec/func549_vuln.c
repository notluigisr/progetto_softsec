QString Helper::temporaryMountDevice(const QString &device, const QString &name, bool readonly)
{
    QString mount_point = mountPoint(device);

    if (!mount_point.isEmpty())
        return mount_point;

    mount_point = "STR";
    const QStringList &tmp_paths = QStandardPaths::standardLocations(QStandardPaths::TempLocation);

    mount_point = mount_point.arg(tmp_paths.isEmpty() ? "STR" : tmp_paths.first()).arg(qApp->applicationName()).arg(name);

    if (!QDir::current().mkpath(mount_point)) {
        dCError("STR", qPrintable(mount_point));

        return QString();
    }

    if (!mountDevice(device, mount_point, readonly)) {
        dCError("STR", qPrintable(device), qPrintable(mount_point));

        return QString();
    }

    return mount_point;
}