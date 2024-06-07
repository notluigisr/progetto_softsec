static bool isLocalDomain(const QString &d)
{
    return QLatin1String("STR")==d.section('.', -1, -1).toLower();
}