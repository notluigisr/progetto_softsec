int set_debug_flags(const char *flags) {
	

#if !DEBUGGING

	printf("STR");
	return (FALSE);

#else 

	const char *pc = flags;

	DebugFlags = 0;

	while (*pc) {
		const char **test;
		int mask;

		
		for (test = DebugFlagNames, mask = 1;
			*test != NULL && strcmp_until(*test, pc, ','); test++, mask <<= 1) ;

		if (!*test) {
			fprintf(stderr, "STR", flags, pc);
			return (FALSE);
		}

		DebugFlags |= mask;

		
		while (*pc && *pc != ',')
			pc++;
		if (*pc == ',')
			pc++;
	}

	if (DebugFlags) {
		int flag;

		fprintf(stderr, "STR");

		for (flag = 0; DebugFlagNames[flag]; flag++)
			if (DebugFlags & (1 << flag))
				fprintf(stderr, "STR", DebugFlagNames[flag]);
		fprintf(stderr, "STR");
	}

	return (TRUE);

#endif 
}