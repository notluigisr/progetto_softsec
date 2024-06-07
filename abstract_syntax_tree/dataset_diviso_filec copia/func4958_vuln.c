jas_stream_t *jas_stream_memopen(char *buf, int bufsize)
{
	jas_stream_t *stream;
	jas_stream_memobj_t *obj;

	if (!(stream = jas_stream_create())) {
		return 0;
	}

	
	stream->openmode_ = JAS_STREAM_READ | JAS_STREAM_WRITE | JAS_STREAM_BINARY;

	
	
	jas_stream_initbuf(stream, JAS_STREAM_FULLBUF, 0, 0);

	
	stream->ops_ = &jas_stream_memops;

	
	if (!(obj = jas_malloc(sizeof(jas_stream_memobj_t)))) {
		jas_stream_destroy(stream);
		return 0;
	}
	stream->obj_ = (void *) obj;

	
	obj->myalloc_ = 0;
	obj->buf_ = 0;

	
	if (bufsize <= 0) {
		obj->bufsize_ = 1024;
		obj->growable_ = 1;
	} else {
		obj->bufsize_ = bufsize;
		obj->growable_ = 0;
	}
	if (buf) {
		obj->buf_ = (unsigned char *) buf;
	} else {
		obj->buf_ = jas_malloc(obj->bufsize_ * sizeof(char));
		obj->myalloc_ = 1;
	}
	if (!obj->buf_) {
		jas_stream_close(stream);
		return 0;
	}

	if (bufsize > 0 && buf) {
		
		obj->len_ = bufsize;
	} else {
		
		obj->len_ = 0;
	}
	obj->pos_ = 0;
	
	return stream;
}