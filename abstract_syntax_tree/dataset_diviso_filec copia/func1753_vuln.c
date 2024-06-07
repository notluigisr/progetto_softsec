set_fflags_platform(struct archive_write_disk *a, int fd, const char *name,
    mode_t mode, unsigned long set, unsigned long clear)
{
	int r;
	const int sf_mask = 0
#ifdef SF_APPEND
	    | SF_APPEND
#endif
#ifdef SF_ARCHIVED
	    | SF_ARCHIVED
#endif
#ifdef SF_IMMUTABLE
	    | SF_IMMUTABLE
#endif
#ifdef SF_NOUNLINK
	    | SF_NOUNLINK
#endif
	;
	(void)mode; 

	if (set == 0  && clear == 0)
		return (ARCHIVE_OK);

	
	if ((r = lazy_stat(a)) != ARCHIVE_OK)
		return (r);

	a->st.st_flags &= ~clear;
	a->st.st_flags |= set;

	

	if (a->user_uid != 0)
		a->st.st_flags &= ~sf_mask;

#ifdef HAVE_FCHFLAGS
	
	if (fd >= 0 && fchflags(fd, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#endif
	
#ifdef HAVE_LCHFLAGS
	if (lchflags(name, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#elif defined(HAVE_CHFLAGS)
	if (S_ISLNK(a->st.st_mode)) {
		archive_set_error(&a->archive, errno,
		    "STR");
		return (ARCHIVE_WARN);
	}
	if (chflags(name, a->st.st_flags) == 0)
		return (ARCHIVE_OK);
#endif
	archive_set_error(&a->archive, errno,
	    "STR");
	return (ARCHIVE_WARN);
}