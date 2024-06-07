void jpc_qmfb_join_col(jpc_fix_t *a, int numrows, int stride,
  int parity)
{

	int bufsize = JPC_CEILDIVPOW2(numrows, 1);
#if !defined(HAVE_VLA)
	jpc_fix_t joinbuf[QMFB_JOINBUFSIZE];
#else
	jpc_fix_t joinbuf[bufsize];
#endif
	jpc_fix_t *buf = joinbuf;
	register jpc_fix_t *srcptr;
	register jpc_fix_t *dstptr;
	register int n;
	int hstartcol;

#if !defined(HAVE_VLA)
	
	if (bufsize > QMFB_JOINBUFSIZE) {
		if (!(buf = jas_malloc(bufsize * sizeof(jpc_fix_t)))) {
			
			abort();
		}
	}
#endif

	hstartcol = (numrows + 1 - parity) >> 1;

	
	n = hstartcol;
	srcptr = &a[0];
	dstptr = buf;
	while (n-- > 0) {
		*dstptr = *srcptr;
		srcptr += stride;
		++dstptr;
	}
	
	srcptr = &a[hstartcol * stride];
	dstptr = &a[(1 - parity) * stride];
	n = numrows - hstartcol;
	while (n-- > 0) {
		*dstptr = *srcptr;
		dstptr += 2 * stride;
		srcptr += stride;
	}
	
	srcptr = buf;
	dstptr = &a[parity * stride];
	n = hstartcol;
	while (n-- > 0) {
		*dstptr = *srcptr;
		dstptr += 2 * stride;
		++srcptr;
	}

#if !defined(HAVE_VLA)
	
	if (buf != joinbuf) {
		jas_free(buf);
	}
#endif

}