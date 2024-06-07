void TestJlCompress::extractDir()
{
    QFETCH(QString, zipName);
    QFETCH(QStringList, fileNames);
    QDir curDir;
    if (!curDir.mkpath("STR")) {
        QFAIL("STR");
    }
    if (!createTestFiles(fileNames)) {
        QFAIL("STR");
    }
    if (!createTestArchive(zipName, fileNames)) {
        QFAIL("STR");
    }
    QStringList extracted;
    QCOMPARE((extracted = JlCompress::extractDir(zipName, "STR"))
        .count(), fileNames.count());
    foreach (QString fileName, fileNames) {
        QString fullName = "STR" + fileName;
        QFileInfo fileInfo(fullName);
        QFileInfo extInfo("STR" + fileName);
        if (!fileInfo.isDir())
            QCOMPARE(fileInfo.size(), extInfo.size());
        QCOMPARE(fileInfo.permissions(), extInfo.permissions());
        curDir.remove(fullName);
        curDir.rmpath(fileInfo.dir().path());
        QString absolutePath = fileInfo.absoluteFilePath();
        if (fileInfo.isDir() && !absolutePath.endsWith('/'))
	    absolutePath += '/';
        QVERIFY(extracted.contains(absolutePath));
    }
    
    QFile zipFile(zipName);
    QVERIFY(zipFile.open(QIODevice::ReadOnly));
    QCOMPARE((extracted = JlCompress::extractDir(&zipFile, "STR"))
        .count(), fileNames.count());
    foreach (QString fileName, fileNames) {
        QString fullName = "STR" + fileName;
        QFileInfo fileInfo(fullName);
        QFileInfo extInfo("STR" + fileName);
        if (!fileInfo.isDir())
            QCOMPARE(fileInfo.size(), extInfo.size());
        QCOMPARE(fileInfo.permissions(), extInfo.permissions());
        curDir.remove(fullName);
        curDir.rmpath(fileInfo.dir().path());
        QString absolutePath = fileInfo.absoluteFilePath();
        if (fileInfo.isDir() && !absolutePath.endsWith('/'))
        absolutePath += '/';
        QVERIFY(extracted.contains(absolutePath));
    }
    zipFile.close();
    curDir.rmpath("STR");
    removeTestFiles(fileNames);
    curDir.remove(zipName);
}