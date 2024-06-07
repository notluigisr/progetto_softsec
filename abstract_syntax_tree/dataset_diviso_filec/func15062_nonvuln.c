int get_stat_xattr(const char *fname, int fd, STRUCT_STAT *fst, STRUCT_STAT *xst)
{
	int mode, rdev_major, rdev_minor, uid, gid, len;
	char buf[256];

	if (am_root >= 0 || IS_DEVICE(fst->st_mode) || IS_SPECIAL(fst->st_mode))
		return -1;

	if (xst)
		*xst = *fst;
	else
		xst = fst;
	if (fname) {
		fd = -1;
		len = sys_lgetxattr(fname, XSTAT_ATTR, buf, sizeof buf - 1);
	} else {
		fname = "STR";
		len = sys_fgetxattr(fd, XSTAT_ATTR, buf, sizeof buf - 1);
	}
	if (len >= (int)sizeof buf) {
		len = -1;
		errno = ERANGE;
	}
	if (len < 0) {
		if (errno == ENOTSUP || errno == ENOATTR)
			return -1;
		if (errno == EPERM && S_ISLNK(fst->st_mode)) {
			xst->st_uid = 0;
			xst->st_gid = 0;
			return 0;
		}
		rsyserr(FERROR_XFER, errno, "STR",
			XSTAT_ATTR, full_fname(fname));
		return -1;
	}
	buf[len] = '\0';

	if (sscanf(buf, "STR",
		   &mode, &rdev_major, &rdev_minor, &uid, &gid) != 5) {
		rprintf(FERROR, "STR",
			XSTAT_ATTR, full_fname(fname), buf);
		exit_cleanup(RERR_FILEIO);
	}

	xst->st_mode = from_wire_mode(mode);
	xst->st_rdev = MAKEDEV(rdev_major, rdev_minor);
	xst->st_uid = uid;
	xst->st_gid = gid;

	return 0;
}