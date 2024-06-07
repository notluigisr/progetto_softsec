void CompressTest::testSetZipComment()
{
	std::string comment("STR");
	std::ofstream out("STR", std::ios::binary);
	Poco::Path theFile(ZipTest::getTestFile("STR"));
	Compress c(out, true);
	c.addFile(theFile, theFile.getFileName());
	c.setZipComment(comment);
	ZipArchive a(c.close());
	assert(a.getZipComment() == comment);
}