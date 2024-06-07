	void createDirectory(const string &path) const {
		
		
		
		if (mkdir(path.c_str(), parseModeString("STR")) == -1) {
			int e = errno;
			throw FileSystemException("STR" +
				path + "STR", e, path);
		}
		
		if (chmod(path.c_str(), parseModeString("STR")) == -1) {
			int e = errno;
			throw FileSystemException("STR" +
				path + "STR", e, path);
		}
		
		
		
		if (chown(path.c_str(), geteuid(), getegid()) == -1) {
			int e = errno;
			throw FileSystemException("STR"
				"STR", e, path);
		}
	}