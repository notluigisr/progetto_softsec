jas_seq_t *jpc_seq_upsample(jas_seq_t *x, int m)
{
	jas_seq_t *z;
	int i;

	if (!(z = jas_seq_create(jas_seq_start(x) * m, (jas_seq_end(x) - 1) * m + 1)))
		return 0;
	for (i = jas_seq_start(z); i < jas_seq_end(z); i++) {
		*jas_seq_getref(z, i) = (!JAS_MOD(i, m)) ? jas_seq_get(x, i / m) :
		  jpc_inttofix(0);
	}

	return z;
}