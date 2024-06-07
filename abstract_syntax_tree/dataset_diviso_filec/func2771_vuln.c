	void initialize(const string &path, bool owner) {
		TRACE_POINT();
		this->path  = path;
		this->owner = owner;
		
		
		if (owner) {
			switch (getFileTypeNoFollowSymlinks(path)) {
			case FT_NONEXISTANT:
				createDirectory(path);
				break;
			case FT_DIRECTORY:
				verifyDirectoryPermissions(path);
				break;
			default:
				throw RuntimeException("STR");
			}
		} else if (getFileType(path) != FT_DIRECTORY) {
			throw RuntimeException("STR" + path +
				"STR");
		}
	}