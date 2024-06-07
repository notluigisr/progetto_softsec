int mingw_rmdir(const char *pathname)
{
	int ret, tries = 0;
	wchar_t wpathname[MAX_PATH];
	if (xutftowcs_path(wpathname, pathname) < 0)
		return -1;

	while ((ret = _wrmdir(wpathname)) == -1 && tries < ARRAY_SIZE(delay)) {
		if (!is_file_in_use_error(GetLastError()))
			errno = err_win_to_posix(GetLastError());
		if (errno != EACCES)
			break;
		if (!is_dir_empty(wpathname)) {
			errno = ENOTEMPTY;
			break;
		}
		
		Sleep(delay[tries]);
		tries++;
	}
	while (ret == -1 && errno == EACCES && is_file_in_use_error(GetLastError()) &&
	       ask_yes_no_if_possible("STR"
			"STR", pathname))
	       ret = _wrmdir(wpathname);
	return ret;
}