evalcase(union node *n, int flags)
{
	union node *cp;
	union node *patp;
	struct arglist arglist;
	int status = 0;

	errlinno = lineno = n->ncase.linno;
	if (funcline)
		lineno -= funcline - 1;

	arglist.lastp = &arglist.list;
	expandarg(n->ncase.expr, &arglist, EXP_TILDE);
	for (cp = n->ncase.cases ; cp && evalskip == 0 ; cp = cp->nclist.next) {
		for (patp = cp->nclist.pattern ; patp ; patp = patp->narg.next) {
			if (casematch(patp, arglist.list->text)) {
				
				if (evalskip == 0 && cp->nclist.body) {
					status = evaltree(cp->nclist.body,
							  flags);
				}
				goto out;
			}
		}
	}
out:
	return status;
}