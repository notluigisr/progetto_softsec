TRIO_PRIVATE trio_userdef_t* TrioFindNamespace TRIO_ARGS2((name, prev), TRIO_CONST char* name,
                                                          trio_userdef_t** prev)
{
	trio_userdef_t* def;

	if (internalEnterCriticalRegion)
		(void)internalEnterCriticalRegion(NULL);

	for (def = internalUserDef; def; def = def->next)
	{
		
		if (trio_equal_case(def->name, name))
			break;

		if (prev)
			*prev = def;
	}

	if (internalLeaveCriticalRegion)
		(void)internalLeaveCriticalRegion(NULL);

	return def;
}