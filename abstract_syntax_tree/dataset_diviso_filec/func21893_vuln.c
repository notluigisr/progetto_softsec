void CompressTest::testManipulatorReplace()
{
	{
		std::ofstream out("STR", std::ios::binary);
		Poco::Path theFile(ZipTest::getTestFile("STR"));
		Compress c(out, true);
		c.addFile(theFile, theFile.getFileName());
		ZipArchive a(c.close());
	}
	ZipManipulator zm("STR", true);
	zm.replaceFile("STR"));
	
	ZipArchive archive=zm.commit();
	assert (archive.findHeader("STR") != archive.headerEnd());
	assert (archive.findHeader("STR") == archive.headerEnd());
}