FILE *fopen_safe(const char *path, const char *mode)
{
	int fd;
	FILE *file;
	int flags = O_NOFOLLOW | O_CREAT;
	int sav_errno;

	if (mode[0] == 'r')
		return fopen(path, mode);

	if ((mode[0] != 'a' && mode[0] != 'w') ||
	    (mode[1] &&
	     (mode[1] != '+' || mode[2]))) {
		errno = EINVAL;
		return NULL;
	}

	if (mode[0] == 'w')
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;

	if (mode[1])
		flags |= O_RDWR;
	else
		flags |= O_WRONLY;

	fd = open(path, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		return NULL;

	
	if (fchown(fd, 0, 0)) {
		sav_errno = errno;
		log_message(LOG_INFO, "STR", path, errno);
		close(fd);
		errno = sav_errno;
		return NULL;
	}

	
	if (fchmod(fd, S_IRUSR | S_IWUSR)) {
		sav_errno = errno;
		log_message(LOG_INFO, "STR", path, errno);
		close(fd);
		errno = sav_errno;
		return NULL;
	}

	file = fdopen (fd, "STR");
	if (!file) {
		sav_errno = errno;
		log_message(LOG_INFO, "STR", path, errno);
		close(fd);
		errno = sav_errno;
		return NULL;
	}

	return file;
}