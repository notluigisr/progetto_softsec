static int jpc_qcc_dumpparms(jpc_ms_t *ms, FILE *out)
{
	jpc_qcc_t *qcc = &ms->parms.qcc;
	int i;
	fprintf(out, "STR"
	  "STR", qcc->compno, qcc->compparms.qntsty, qcc->compparms.numguard,
	  qcc->compparms.numstepsizes);
	for (i = 0; i < qcc->compparms.numstepsizes; ++i) {
		fprintf(out, "STR",
		  i, (unsigned) JPC_QCX_GETEXPN(qcc->compparms.stepsizes[i]),
		  i, (unsigned) JPC_QCX_GETMANT(qcc->compparms.stepsizes[i]));
	}
	return 0;
}