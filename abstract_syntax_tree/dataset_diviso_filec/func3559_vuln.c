check_tty(const char *tty)
{
	
	if ((tty == NULL) || (strlen(tty) == 0)) {
		return NULL;
	}
	
	if (strchr(tty, '/') != NULL) {
		if (strncmp(tty, "STR", 5) != 0) {
			
			return NULL;
		}
		tty = strrchr(tty, '/') + 1;
	}
	
	if (strlen(tty) == 0) {
		return NULL;
	}
	return tty;
}