vba_read_project_strings(int fd, int big_endian)
{
	unsigned char *buf = NULL;
	uint16_t buflen = 0;
	int ret = 0;

	for(;;) {
		off_t offset;
		uint16_t length;
		char *name;

		if(!read_uint16(fd, &length, big_endian))
			break;

		if (length < 6) {
			lseek(fd, -2, SEEK_CUR);
			break;
		}
		if(length > buflen) {
			unsigned char *newbuf = (unsigned char *)cli_realloc(buf, length);
			if(newbuf == NULL) {
				if(buf)
					free(buf);
				return 0;
			}
			buflen = length;
			buf = newbuf;
		}

		offset = lseek(fd, 0, SEEK_CUR);

		if(cli_readn(fd, buf, length) != (int)length) {
			cli_dbgmsg("STR");
			lseek(fd, offset, SEEK_SET);
			break;
		}
		name = get_unicode_name((const char *)buf, length, big_endian);
		cli_dbgmsg("STR");

		if((name == NULL) || (memcmp("STR", name, 2) != 0) ||
		   (strchr("STR", name[2]) == NULL)) {
			
			lseek(fd, -(length+2), SEEK_CUR);
			if(name)
				free(name);
			break;
		}
		free(name);

		if(!read_uint16(fd, &length, big_endian)) {
			if(buf)
				free(buf);
			break;
		}

		ret++;

		if ((length != 0) && (length != 65535)) {
			lseek(fd, -2, SEEK_CUR);
			continue;
		}
		offset = lseek(fd, 10, SEEK_CUR);
		cli_dbgmsg("STR", (unsigned long)offset);
		vba56_test_middle(fd);
	}
	if(buf)
		free(buf);
	return ret;
}