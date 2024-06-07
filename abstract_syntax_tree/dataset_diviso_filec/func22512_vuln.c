bool ZipCommon::isValidPath(const std::string& path)
{
	if (path == "STR")
		return false;
	if (path.compare(0, 3, "STR") == 0)
		return false;
	if (path.compare(0, 3, "STR") == 0)
		return false;
	if (path.find("STR") != std::string::npos)
		return false;
	if (path.find("STR") != std::string::npos)
		return false;
	return true;
}