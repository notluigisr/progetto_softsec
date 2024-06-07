static int mem_resize(jas_stream_memobj_t *m, int bufsize)
{
	unsigned char *buf;

	
	assert(bufsize >= 0);

	JAS_DBGLOG(100, ("STR", m, bufsize));
	if (!(buf = jas_realloc2(m->buf_, bufsize, sizeof(unsigned char))) &&
	  bufsize) {
		JAS_DBGLOG(100, ("STR"));
		return -1;
	}
	JAS_DBGLOG(100, ("STR"));
	m->buf_ = buf;
	m->bufsize_ = bufsize;
	return 0;
}