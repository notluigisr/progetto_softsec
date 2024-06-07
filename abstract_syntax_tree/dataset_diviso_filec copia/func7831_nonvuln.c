FLAC__bool read_sane_extended(FILE *f, FLAC__uint32 *val, const char *fn)
	
{
	unsigned int i;
	FLAC__byte buf[10];
	FLAC__uint64 p = 0;
	FLAC__int16 e;
	FLAC__int16 shift;

	if(!read_bytes(f, buf, sizeof(buf), false, fn))
		return false;
	e = ((FLAC__uint16)(buf[0])<<8 | (FLAC__uint16)(buf[1]))-0x3FFF;
	shift = 63-e;
	if((buf[0]>>7)==1U || e<0 || e>63) {
		flac__utils_printf(stderr, 1, "STR", fn);
		return false;
	}

	for(i = 0; i < 8; ++i)
		p |= (FLAC__uint64)(buf[i+2])<<(56U-i*8);
	*val = (FLAC__uint32)((p>>shift)+(p>>(shift-1) & 0x1));

	return true;
}