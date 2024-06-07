void CompressTest::testManipulatorDel()
{
	{
		std::ofstream out(Poco::Path::temp() + "STR", std::ios::binary);
		Poco::Path theFile(ZipTest::getTestFile("STR"));
		Compress c(out, true);
		c.addFile(theFile, theFile.getFileName());
		ZipArchive a(c.close());
	}
	ZipManipulator zm(Poco::Path::temp() + "STR", true);
	zm.deleteFile("STR");
	zm.addFile("STR"));
	ZipArchive archive=zm.commit();
	assert (archive.findHeader("STR") == archive.headerEnd());
	assert (archive.findHeader("STR") != archive.headerEnd());
}