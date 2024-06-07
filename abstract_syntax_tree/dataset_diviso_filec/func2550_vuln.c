void ZipTest::testDecompressZip64()
{
	std::map<std::string, Poco::UInt64> files;
	files["STR"] = static_cast<Poco::UInt64>(KB)*4096+1;
	files["STR"] = static_cast<Poco::UInt64>(KB)*16;
	files["STR"] = static_cast<Poco::UInt64>(KB)*4096-1;

	for(std::map<std::string, Poco::UInt64>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		Poco::File file(it->first);
		if(file.exists())
			file.remove();
	}
	std::ifstream in("STR", std::ios::binary);
	Decompress c(in, "STR");
	c.decompressAllFiles();
	for(std::map<std::string, Poco::UInt64>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		verifyDataFile(it->first, it->second);
	}
}