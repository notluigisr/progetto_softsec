static int jpc_rgn_dumpparms(jpc_ms_t *ms, FILE *out)
{
	jpc_rgn_t *rgn = &ms->parms.rgn;
	fprintf(out, "STR",
	  rgn->compno, rgn->roisty, rgn->roishift);
	return 0;
}