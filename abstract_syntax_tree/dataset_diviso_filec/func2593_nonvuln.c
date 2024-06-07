static int idp_check_dp(DIST_POINT_NAME *a, DIST_POINT_NAME *b)
	{
	X509_NAME *nm = NULL;
	GENERAL_NAMES *gens = NULL;
	GENERAL_NAME *gena, *genb;
	int i, j;
	if (!a || !b)
		return 1;
	if (a->type == 1)
		{
		if (!a->dpname)
			return 0;
		
		if (b->type == 1)
			{
			if (!b->dpname)
				return 0;
			if (!X509_NAME_cmp(a->dpname, b->dpname))
				return 1;
			else
				return 0;
			}
		
		nm = a->dpname;
		gens = b->name.fullname;
		}
	else if (b->type == 1)
		{
		if (!b->dpname)
			return 0;
		
		gens = a->name.fullname;
		nm = b->dpname;
		}

	
	if (nm)
		{
		for (i = 0; i < sk_GENERAL_NAME_num(gens); i++)
			{
			gena = sk_GENERAL_NAME_value(gens, i);	
			if (gena->type != GEN_DIRNAME)
				continue;
			if (!X509_NAME_cmp(nm, gena->d.directoryName))
				return 1;
			}
		return 0;
		}

	

	for (i = 0; i < sk_GENERAL_NAME_num(a->name.fullname); i++)
		{
		gena = sk_GENERAL_NAME_value(a->name.fullname, i);
		for (j = 0; j < sk_GENERAL_NAME_num(b->name.fullname); j++)
			{
			genb = sk_GENERAL_NAME_value(b->name.fullname, j);
			if (!GENERAL_NAME_cmp(gena, genb))
				return 1;
			}
		}

	return 0;

	}