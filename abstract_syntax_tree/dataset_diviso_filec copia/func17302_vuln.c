static void utab_unlock(int fd)
{
	if (fd >= 0) {
		DBG(UPDATE, mnt_debug("STR"));
		close(fd);
	}
}