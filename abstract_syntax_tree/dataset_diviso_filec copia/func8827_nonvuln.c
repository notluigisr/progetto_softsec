UpdateControlFile(void)
{
	int			fd;

	INIT_CRC32(ControlFile->crc);
	COMP_CRC32(ControlFile->crc,
			   (char *) ControlFile,
			   offsetof(ControlFileData, crc));
	FIN_CRC32(ControlFile->crc);

	fd = BasicOpenFile(XLOG_CONTROL_FILE,
					   O_RDWR | PG_BINARY,
					   S_IRUSR | S_IWUSR);
	if (fd < 0)
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("STR",
						XLOG_CONTROL_FILE)));

	errno = 0;
	if (write(fd, ControlFile, sizeof(ControlFileData)) != sizeof(ControlFileData))
	{
		
		if (errno == 0)
			errno = ENOSPC;
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("STR")));
	}

	if (pg_fsync(fd) != 0)
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("STR")));

	if (close(fd))
		ereport(PANIC,
				(errcode_for_file_access(),
				 errmsg("STR")));
}