	void createDirectory(const string &path) const {
		
		
		
		if (mkdir(path.c_str(), parseModeString("STR")) == -1) {
			int e = errno;
			throw FileSystemException("STR" +
				path + "STR", e, path);
		}
	}