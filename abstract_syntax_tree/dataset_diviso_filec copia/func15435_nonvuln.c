static int bmp_getint16(jas_stream_t *in, int_fast16_t *val)
{
	int lo;
	int hi;
	if ((lo = jas_stream_getc(in)) == EOF || (hi = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	if (val) {
		*val = (hi << 8) | lo;
	}
	return 0;
}