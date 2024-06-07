void CompressTest::testZip64()
{
	std::cout << std::endl;
	std::map<std::string, Poco::UInt64> files;
	files["STR"] = static_cast<Poco::UInt64>(KB)*4096+1;
	files["STR"] = static_cast<Poco::UInt64>(KB)*16;
	files["STR"] = static_cast<Poco::UInt64>(KB)*4096-1;
	
	for(std::map<std::string, Poco::UInt64>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		std::cout << '\t' << "STR" << std::endl;
		createDataFile(it->first, it->second);
	}
	std::ofstream out("STR", std::ios::binary | std::ios::trunc);
	Compress c(out, true, true);
	for(std::map<std::string, Poco::UInt64>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		const std::string& path = it->first;
		std::cout << '\t' << "STR" << std::endl;
		c.addFile(path, path, ZipCommon::CM_STORE);
	}
	ZipArchive a(c.close());
	for(std::map<std::string, Poco::UInt64>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		const std::string& path = it->first;
		Poco::UInt64 size = it->second;
		ZipArchive::FileHeaders::const_iterator it2 = a.findHeader(path);
		assert (it2 != a.headerEnd());
		const Poco::Zip::ZipLocalFileHeader& file = it2->second;
		assert(file.getUncompressedSize() == size);
		assert(file.getCompressedSize() == size);
	}
}