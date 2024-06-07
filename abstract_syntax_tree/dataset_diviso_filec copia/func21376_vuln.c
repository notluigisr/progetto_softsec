void jpc_qmfb_split_row(jpc_fix_t *a, int numcols, int parity)
{

	int bufsize = JPC_CEILDIVPOW2(numcols, 1);
#if !defined(HAVE_VLA)
	jpc_fix_t splitbuf[QMFB_SPLITBUFSIZE];
#else
	jpc_fix_t splitbuf[bufsize];
#endif
	jpc_fix_t *buf = splitbuf;
	register jpc_fix_t *srcptr;
	register jpc_fix_t *dstptr;
	register int n;
	register int m;
	int hstartcol;

#if !defined(HAVE_VLA)
	
	if (bufsize > QMFB_SPLITBUFSIZE) {
		if (!(buf = jas_malloc(bufsize * sizeof(jpc_fix_t)))) {
			
			abort();
		}
	}
#endif

	if (numcols >= 2) {
		hstartcol = (numcols + 1 - parity) >> 1;
		m = (parity) ? hstartcol : (numcols - hstartcol);
		
		n = m;
		dstptr = buf;
		srcptr = &a[1 - parity];
		while (n-- > 0) {
			*dstptr = *srcptr;
			++dstptr;
			srcptr += 2;
		}
		
		dstptr = &a[1 - parity];
		srcptr = &a[2 - parity];
		n = numcols - m - (!parity);
		while (n-- > 0) {
			*dstptr = *srcptr;
			++dstptr;
			srcptr += 2;
		}
		
		dstptr = &a[hstartcol];
		srcptr = buf;
		n = m;
		while (n-- > 0) {
			*dstptr = *srcptr;
			++dstptr;
			++srcptr;
		}
	}

#if !defined(HAVE_VLA)
	
	if (buf != splitbuf) {
		jas_free(buf);
	}
#endif

}