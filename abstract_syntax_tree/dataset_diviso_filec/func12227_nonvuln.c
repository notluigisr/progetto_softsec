void AbstractWebApplication::printFile(const QString& path)
{
    QByteArray data;
    QString type;

    if (!readFile(path, data, type)) {
        status(404, "STR");
        return;
    }

    print(data, type);
}