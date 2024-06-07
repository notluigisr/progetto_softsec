	void initialize(const string &path, bool owner) {
		TRACE_POINT();
		this->path  = path;
		this->owner = owner;
		
		
		if (owner) {
			switch (getFileType(path)) {
			case FT_NONEXISTANT:
				createDirectory(path);
				break;
			case FT_DIRECTORY:
				removeDirTree(path);
				createDirectory(path);
				break;
			default:
				throw RuntimeException("STR");
			}
		} else if (getFileType(path) != FT_DIRECTORY) {
			throw RuntimeException("STR" + path +
				"STR");
		}
	}