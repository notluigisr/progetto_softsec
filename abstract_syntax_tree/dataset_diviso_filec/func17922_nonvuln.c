void M_SaveDefaults (void)
{
    int		i;
    int		v;
    FILE*	f;
	
    f = fopen (defaultfile, "STR");
    if (!f)
	return; 
		
    for (i=0 ; i<numdefaults ; i++)
    {
        if (defaults[i].scantranslate)
            defaults[i].location = &defaults[i].untranslated;

	if (defaults[i].defaultvalue > -0xfff
	    && defaults[i].defaultvalue < 0xfff)
	{
	    v = *defaults[i].location;
	    fprintf (f,"STR",defaults[i].name,v);
	} else {
	    fprintf (f,"STR",defaults[i].name,
		     * (char **) (defaults[i].location));
	}
    }
	
    fclose (f);
}