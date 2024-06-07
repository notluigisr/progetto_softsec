strtoargvsub(isc_mem_t *mctx, char *s, unsigned int *argcp,
	     char ***argvp, unsigned int n)
{
	isc_result_t result;

	
	while (*s == ' ' || *s == '\t')
		s++;

	if (*s == '\0') {
		
		*argcp = n;
		*argvp = isc_mem_get(mctx, n * sizeof(char *));
		if (*argvp == NULL)
			return (ISC_R_NOMEMORY);
	} else {
		char *p = s;
		while (*p != ' ' && *p != '\t' && *p != '\0')
			p++;
		if (*p != '\0')
			*p++ = '\0';

		result = strtoargvsub(mctx, p, argcp, argvp, n + 1);
		if (result != ISC_R_SUCCESS)
			return (result);
		(*argvp)[n] = s;
	}
	return (ISC_R_SUCCESS);
}