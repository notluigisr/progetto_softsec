void CompressTest::testSingleFile()
{
	std::ofstream out("STR", std::ios::binary);
	Poco::Path theFile(ZipTest::getTestFile("STR"));
	Compress c(out, true);
	c.addFile(theFile, theFile.getFileName());
	ZipArchive a(c.close());
}