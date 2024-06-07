static void fast_csum(__sum16 *csum,
		      const unsigned char *optr,
		      const unsigned char *nptr,
		      int offset)
{
	unsigned char s[4];

	if (offset & 1) {
		s[0] = s[2] = 0;
		s[1] = ~*optr;
		s[3] = *nptr;
	} else {
		s[1] = s[3] = 0;
		s[0] = ~*optr;
		s[2] = *nptr;
	}

	*csum = csum_fold(csum_partial(s, 4, ~csum_unfold(*csum)));
}