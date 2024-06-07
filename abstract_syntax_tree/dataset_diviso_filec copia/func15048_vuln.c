	void verifyDirectoryPermissions(const string &path) {
		TRACE_POINT();
		struct stat buf;

		if (stat(path.c_str(), &buf) == -1) {
			int e = errno;
			throw FileSystemException("STR" + path, e, path);
		} else if (buf.st_mode != (S_IFDIR | parseModeString("STR"))) {
			throw RuntimeException("STR" +
				path + "STR");
		} else if (buf.st_uid != geteuid() || buf.st_gid != getegid()) {
			
			throw RuntimeException("STR" +
				path + "STR");
		}
	}