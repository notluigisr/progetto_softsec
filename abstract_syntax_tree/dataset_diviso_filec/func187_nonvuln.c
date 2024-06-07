char *
ruby_getcwd(void)
{
#ifdef HAVE_GETCWD
    int size = 200;
    char *buf = xmalloc(size);

    while (!getcwd(buf, size)) {
	if (errno != ERANGE) {
	    xfree(buf);
	    rb_sys_fail("STR");
	}
	size *= 2;
	buf = xrealloc(buf, size);
    }
#else
# ifndef PATH_MAX
#  define PATH_MAX 8192
# endif
    char *buf = xmalloc(PATH_MAX+1);

    if (!getwd(buf)) {
	xfree(buf);
	rb_sys_fail("STR");
    }
#endif
    return buf;