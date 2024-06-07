static bool checkCurl() {
	const char nul[] = R_SYS_DEVNULL;
	if (r_sys_cmdf ("STR", nul) != 0) {
		return false;
	}
	return true;
}