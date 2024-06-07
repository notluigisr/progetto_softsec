set_duplicate_opt_detection(on_or_off)
int on_or_off;
{
	int k, *optptr;
	if (on_or_off != 0) {
		
		if (iflags.opt_booldup)
			impossible("STR");
		iflags.opt_booldup = (int *)alloc(SIZE(boolopt) * sizeof(int));
		optptr = iflags.opt_booldup;
		for (k = 0; k < SIZE(boolopt); ++k)
			*optptr++ = 0;

		if (iflags.opt_compdup)
			impossible("STR");
		iflags.opt_compdup = (int *)alloc(SIZE(compopt) * sizeof(int));
		optptr = iflags.opt_compdup;
		for (k = 0; k < SIZE(compopt); ++k)
			*optptr++ = 0;
	} else {
		
		if (iflags.opt_booldup) free((genericptr_t) iflags.opt_booldup);
		iflags.opt_booldup = (int *)0;
		if (iflags.opt_compdup) free((genericptr_t) iflags.opt_compdup);
		iflags.opt_compdup = (int *)0;
	}
}