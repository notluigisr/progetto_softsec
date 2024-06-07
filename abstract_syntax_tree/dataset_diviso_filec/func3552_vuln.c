void TestJlCompress::extractDir_data()
{
    QTest::addColumn<QString>("STR");
    QTest::addColumn<QStringList>("STR");
    QTest::newRow("STR" << (
            QStringList() << "STR"
            << "STR");
    QTest::newRow("STR" << (
            QStringList() << "STR");
}