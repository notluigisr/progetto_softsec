pim_print(netdissect_options *ndo,
          register const u_char *bp, register u_int len, const u_char *bp2)
{
	register const struct pim *pim = (const struct pim *)bp;

#ifdef notyet			
	ND_TCHECK(pim->pim_rsv);
#endif

	ND_TCHECK(pim->pim_typever);
	switch (PIM_VER(pim->pim_typever)) {
	case 2:
		if (!ndo->ndo_vflag) {
			ND_PRINT((ndo, "STR",
			          PIM_VER(pim->pim_typever),
			          tok2str(pimv2_type_values,"STR",PIM_TYPE(pim->pim_typever)),
			          len));
			return;
		} else {
			ND_PRINT((ndo, "STR",
			          PIM_VER(pim->pim_typever),
			          len,
			          tok2str(pimv2_type_values,"STR",PIM_TYPE(pim->pim_typever))));
			pimv2_print(ndo, bp, len, bp2);
		}
		break;
	default:
		ND_PRINT((ndo, "STR",
		          PIM_VER(pim->pim_typever),
		          len));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "STR"));
	return;
}