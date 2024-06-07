void CompressTest::testDirectory()
{
	std::ofstream out("STR", std::ios::binary);
	Poco::File aFile("STR");
	if (aFile.exists())
		aFile.remove(true);
	Poco::File aDir("STR");
	aDir.createDirectories();
	Poco::File aDir2("STR");
	aDir2.createDirectories();
	Poco::File aF("STR");
	aF.createFile();
	Poco::FileOutputStream fos(aF.path());
	fos << "STR";
	fos.close();

	Poco::Path theFile(aFile.path());
	theFile.makeDirectory();
	Compress c(out, true);
	c.addRecursive(theFile, ZipCommon::CL_MAXIMUM, false, theFile);
	ZipArchive a(c.close());
}