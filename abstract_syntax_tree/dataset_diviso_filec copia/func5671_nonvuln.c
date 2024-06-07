int jas_stream_rewind(jas_stream_t *stream)
{
	JAS_DBGLOG(100, ("STR", stream));
	return jas_stream_seek(stream, 0, SEEK_SET);
}