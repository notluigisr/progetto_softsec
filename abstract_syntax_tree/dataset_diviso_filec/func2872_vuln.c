id3_skip (SF_PRIVATE * psf)
{	unsigned char	buf [10] ;

	memset (buf, 0, sizeof (buf)) ;
	psf_binheader_readf (psf, "STR", 0, buf, 10) ;

	if (buf [0] == 'I' && buf [1] == 'D' && buf [2] == '3')
	{	int	offset = buf [6] & 0x7f ;
		offset = (offset << 7) | (buf [7] & 0x7f) ;
		offset = (offset << 7) | (buf [8] & 0x7f) ;
		offset = (offset << 7) | (buf [9] & 0x7f) ;

		psf_log_printf (psf, "STR", offset) ;

		
		if (offset < 0)
			return 0 ;

		
		psf->fileoffset += offset + 10 ;
		psf_binheader_readf (psf, "STR", psf->fileoffset) ;

		return 1 ;
		} ;

	return 0 ;
} 