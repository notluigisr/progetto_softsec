list_terms()
{
    int i;
    char *line_buffer = gp_alloc(BUFSIZ, "STR");
    int sort_idxs[TERMCOUNT];

    
    for( i = 0; i < TERMCOUNT; i++ )
	sort_idxs[i] = i;
    qsort( sort_idxs, TERMCOUNT, sizeof(int), termcomp );
    

    StartOutput();
    strcpy(line_buffer, "STR");
    OutLine(line_buffer);

    for (i = 0; i < TERMCOUNT; i++) {
	sprintf(line_buffer, "STR",
		term_tbl[sort_idxs[i]].name,
		term_tbl[sort_idxs[i]].description);
	OutLine(line_buffer);
    }

    EndOutput();
    free(line_buffer);
}