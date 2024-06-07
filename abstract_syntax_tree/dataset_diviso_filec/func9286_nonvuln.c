FLAC__bool read_uint32(FILE *f, FLAC__bool big_endian, FLAC__uint32 *val, const char *fn)
{
	if(!read_bytes(f, (FLAC__byte*)val, 4, false, fn))
		return false;
	if(is_big_endian_host_ != big_endian) {
		FLAC__byte tmp, *b = (FLAC__byte*)val;
		tmp = b[3]; b[3] = b[0]; b[0] = tmp;
		tmp = b[2]; b[2] = b[1]; b[1] = tmp;
	}
	return true;
}