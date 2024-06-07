void M_LoadDefaults (void)
{
    int		i;
    int		len;
    FILE*	f;
    char	def[80];
    char	strparm[100];
    char*	newstring;
    int		parm;
    boolean	isstring;
    
    
    numdefaults = sizeof(defaults)/sizeof(defaults[0]);
    for (i=0 ; i<numdefaults ; i++)
	*defaults[i].location = defaults[i].defaultvalue;
    
    
    i = M_CheckParm ("STR");
    if (i && i<myargc-1)
    {
	defaultfile = myargv[i+1];
	printf ("STR",defaultfile);
    }
    else
	defaultfile = basedefault;
    
    
    f = fopen (defaultfile, "STR");
    if (f)
    {
	while (!feof(f))
	{
	    isstring = false;
	    if (fscanf (f, "STR", def, strparm) == 2)
	    {
		if (strparm[0] == '"')
		{
		    
		    isstring = true;
		    len = strlen(strparm);
		    newstring = (char *) malloc(len);
		    strparm[len-1] = 0;
		    strcpy(newstring, strparm+1);
		}
		else if (strparm[0] == '0' && strparm[1] == 'x')
		    sscanf(strparm+2, "STR", &parm);
		else
		    sscanf(strparm, "STR", &parm);
		for (i=0 ; i<numdefaults ; i++)
		    if (!strcmp(def, defaults[i].name))
		    {
			if (!isstring)
			    *defaults[i].location = parm;
			else
			    *defaults[i].location =
				(int) newstring;
			break;
		    }
	    }
	}
		
	fclose (f);
    }

    for (i = 0; i < numdefaults; i++)
    {
        if (defaults[i].scantranslate)
        {
            parm = *defaults[i].location;
            defaults[i].untranslated = parm;
            *defaults[i].location = scantokey[parm];
        }
    }
}