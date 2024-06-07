	TEST_METHOD(5) {
		
		
		string path, path2;
		{
			ServerInstanceDir dir(parentDir + "STR", false);
			ServerInstanceDir dir2(parentDir + "STR", false);
			dir2.detach();
			path = dir.getPath();
			path2 = dir2.getPath();
		}
		ensure_equals(getFileType(path), FT_DIRECTORY);
		ensure_equals(getFileType(path2), FT_DIRECTORY);
	}