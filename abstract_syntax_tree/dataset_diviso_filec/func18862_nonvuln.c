static void jp2_pclr_dumpdata(jp2_box_t *box, FILE *out)
{
	jp2_pclr_t *pclr = &box->data.pclr;
	unsigned int i;
	int j;
	fprintf(out, "STR", (int) pclr->numlutents,
	  (int) pclr->numchans);
	for (i = 0; i < pclr->numlutents; ++i) {
		for (j = 0; j < pclr->numchans; ++j) {
			fprintf(out, "STR", i, j, pclr->lutdata[i * pclr->numchans + j]);
		}
	}
}