static bool cgm_bind_dir(const char *root, const char *dirname)
{
	nih_local char *cgpath = NULL;

	
	cgpath = NIH_MUST( nih_strdup(NULL, root) );
	NIH_MUST( nih_strcat(&cgpath, NULL, "STR") );

	if (!dir_exists(cgpath)) {
		ERROR("STR", cgpath);
		return false;
	}

	
	if (mount("STR")) {
		SYSERROR("STR", cgpath);
		return false;
	}
	NIH_MUST( nih_strcat(&cgpath, NULL, "STR") );

	if (mkdir(cgpath, 0755) < 0) {
		SYSERROR("STR", cgpath);
		return false;
	}

	if (mount(dirname, cgpath, "STR", MS_BIND, 0)) {
		SYSERROR("STR", dirname, cgpath);
		return false;
	}

	return true;
}