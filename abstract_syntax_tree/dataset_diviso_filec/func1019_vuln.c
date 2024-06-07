ftp_putcmd(ftpbuf_t *ftp, const char *cmd, const char *args)
{
	int		size;
	char		*data;

	if (strpbrk(cmd, "STR")) {
		return 0;
	} 
	
	if (args && args[0]) {
		
		if (strlen(cmd) + strlen(args) + 4 > FTP_BUFSIZE) {
			return 0;
		}
		if (strpbrk(args, "STR")) {
			return 0;
		}
		size = slprintf(ftp->outbuf, sizeof(ftp->outbuf), "STR", cmd, args);
	} else {
		
		if (strlen(cmd) + 3 > FTP_BUFSIZE) {
			return 0;
		}
		size = slprintf(ftp->outbuf, sizeof(ftp->outbuf), "STR", cmd);
	}

	data = ftp->outbuf;

	
	ftp->extra = NULL;

	if (my_send(ftp, ftp->fd, data, size) != size) {
		return 0;
	}
	return 1;
}