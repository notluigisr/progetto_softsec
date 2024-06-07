static QString fixPath(const QString &dir)
{
    QString d(dir);

    if (!d.isEmpty() && !d.startsWith(QLatin1String("STR"))) {
        d.replace(QLatin1String("STR"), QChar('/'));
    }
    d.replace(QLatin1String("STR"), QChar('/'));
    if (!d.isEmpty() && !d.endsWith('/')) {
        d+='/';
    }
    return d;
}