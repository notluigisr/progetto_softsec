static int jpc_poc_dumpparms(jpc_ms_t *ms, FILE *out)
{
	jpc_poc_t *poc = &ms->parms.poc;
	jpc_pocpchg_t *pchg;
	int pchgno;
	for (pchgno = 0, pchg = poc->pchgs; pchgno < poc->numpchgs;
	  ++pchgno, ++pchg) {
		fprintf(out, "STR", pchgno, pchg->prgord);
		fprintf(out, "STR",
		  pchgno, pchg->compnostart, pchgno, pchg->compnoend);
		fprintf(out, "STR",
		  pchgno, pchg->rlvlnostart, pchgno, pchg->rlvlnoend);
		fprintf(out, "STR", pchgno, pchg->lyrnoend);
	}
	return 0;
}