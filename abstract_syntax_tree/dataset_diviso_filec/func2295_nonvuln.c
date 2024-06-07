FLAC__bool read_uint16(FILE *f, FLAC__bool big_endian, FLAC__uint16 *val, const char *fn)
{
	if(!read_bytes(f, (FLAC__byte*)val, 2, false, fn))
		return false;
	if(is_big_endian_host_ != big_endian) {
		FLAC__byte tmp, *b = (FLAC__byte*)val;
		tmp = b[1]; b[1] = b[0]; b[0] = tmp;
	}
	return true;
}