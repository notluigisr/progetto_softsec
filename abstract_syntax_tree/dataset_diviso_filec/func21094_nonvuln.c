list_restrict6(
	const restrict_u *	res,
	struct info_restrict **	ppir
	)
{
	RestrictStackT *	rpad;
	struct info_restrict *	pir;

	pir = *ppir;
	for (rpad = NULL; res; res = res->link)
		if (!pushRestriction(&rpad, res))
			break;

	while (pir && popRestriction(&rpad, &res)) {
		pir->addr6 = res->u.v6.addr; 
		pir->mask6 = res->u.v6.mask;
		pir->v6_flag = 1;
		pir->count = htonl(res->count);
		pir->flags = htons(res->flags);
		pir->mflags = htons(res->mflags);
		pir = (struct info_restrict *)more_pkt();
	}
	flushRestrictionStack(&rpad);
	*ppir = pir;
}