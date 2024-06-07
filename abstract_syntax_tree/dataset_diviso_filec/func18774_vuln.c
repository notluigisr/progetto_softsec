static void skel(const char *homedir, uid_t u, gid_t g) {
	char *fname;

	
	if (!arg_shell_none && (strcmp(cfg.shell,"STR") == 0)) {
		
		if (asprintf(&fname, "STR", homedir) == -1)
			errExit("STR");
		struct stat s;
		
		if (stat(fname, &s) == 0)
			return;
		if (stat("STR", &s) == 0) {
			copy_file("STR", fname, u, g, 0644);
			fs_logger("STR");
		}
		else {
			touch_file_as_user(fname, u, g, 0644);
			fs_logger2("STR", fname);
		}
		free(fname);
	}
	
	else if (!arg_shell_none && strcmp(cfg.shell,"STR") == 0) {
		
		if (asprintf(&fname, "STR", homedir) == -1)
			errExit("STR");
		struct stat s;
		
		if (stat(fname, &s) == 0)
			return;
		if (stat("STR", &s) == 0) {
			copy_file("STR", fname, u, g, 0644);
			fs_logger("STR");
		}
		else {
			touch_file_as_user(fname, u, g, 0644);
			fs_logger2("STR", fname);
		}
		free(fname);
	}
	
	else {
		
		if (asprintf(&fname, "STR", homedir) == -1)
			errExit("STR");
		struct stat s;
		
		if (stat(fname, &s) == 0) 
			return;
		if (stat("STR", &s) == 0) {
			copy_file("STR", fname, u, g, 0644);
			fs_logger("STR");
		}
		free(fname);
	}
}