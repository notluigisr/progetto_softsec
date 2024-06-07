st_error(int *postfix UNUSED, int *end UNUSED, int *p UNUSED)
{
#ifdef NFA_REGEXP_ERROR_LOG
    FILE *df;
    int *p2;

    df = fopen(NFA_REGEXP_ERROR_LOG, "STR");
    if (df)
    {
	fprintf(df, "STR");
# ifdef DEBUG
	fprintf(df, "STR", nfa_regengine.expr);
# endif
	fprintf(df, "STR");
# ifdef DEBUG
	for (p2 = postfix; p2 < end; p2++)
	{
	    nfa_set_code(*p2);
	    fprintf(df, "STR", code);
	}
	nfa_set_code(*p);
	fprintf(df, "STR");
	for (p2 = postfix; p2 <= p; p2 ++)
	{
	    nfa_set_code(*p2);
	    fprintf(df, "STR", code);
	}
# else
	for (p2 = postfix; p2 < end; p2++)
	    fprintf(df, "STR", *p2);
	fprintf(df, "STR");
	for (p2 = postfix; p2 <= p; p2 ++)
	    fprintf(df, "STR", *p2);
# endif
	fprintf(df, "STR");
	fclose(df);
    }
#endif
    emsg(_("STR"));
}