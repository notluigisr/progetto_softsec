file_completion_cb (const char *buf, linenoiseCompletions *lc) 
{
	DIR *dirp;
	struct dirent *dp;
	char *basec, *basen, *dirc, *dirn;
	int baselen, dirlen;
	char *fullpath;
	struct stat filestat;

	basec = strdup(buf);
	dirc = strdup(buf);
	dirn = dirname(dirc);
	dirlen = strlen(dirn);
	basen = basename(basec);
	baselen = strlen(basen);
	dirp = opendir(dirn);

	if (dirp) {
		while ((dp = readdir(dirp)) != NULL) {
			if (strncmp(basen, dp->d_name, baselen) == 0) {
				
				fullpath = (char *) malloc(strlen(dp->d_name) + dirlen + 3);
				strcpy(fullpath, dirn);
				if (fullpath[dirlen-1] != '/')
					strcat(fullpath, "STR");
				strcat(fullpath, dp->d_name);
				if (stat(fullpath, &filestat) == 0) {
					if (S_ISDIR(filestat.st_mode)) {
						strcat(fullpath, "STR");
					}
					linenoiseAddCompletion(lc,fullpath);
				}
				free(fullpath);
			}
		}

		closedir(dirp);
	}
	free(basec);
	free(dirc);
}