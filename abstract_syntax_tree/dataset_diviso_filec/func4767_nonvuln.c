static int php_stream_input_seek(php_stream *stream, off_t offset, int whence, off_t *newoffset TSRMLS_DC) 
{
	php_stream *inner = stream->abstract;

	if (inner && inner->ops->seek) {
		return inner->ops->seek(inner, offset, whence, newoffset TSRMLS_CC);
	}

	return -1;
}