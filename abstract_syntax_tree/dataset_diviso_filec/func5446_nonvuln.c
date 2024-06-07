static int php_stdiop_flush(php_stream *stream)
{
	php_stdio_stream_data *data = (php_stdio_stream_data*)stream->abstract;

	assert(data != NULL);

	
	if (data->file) {
		return fflush(data->file);
	}
	return 0;
}