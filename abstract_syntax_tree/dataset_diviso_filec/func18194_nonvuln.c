MergeAffix(IspellDict *Conf, int a1, int a2)
{
	char	  **ptr;

	while (Conf->nAffixData + 1 >= Conf->lenAffixData)
	{
		Conf->lenAffixData *= 2;
		Conf->AffixData = (char **) repalloc(Conf->AffixData,
										sizeof(char *) * Conf->lenAffixData);
	}

	ptr = Conf->AffixData + Conf->nAffixData;
	*ptr = cpalloc(strlen(Conf->AffixData[a1]) +
				   strlen(Conf->AffixData[a2]) +
				   1  + 1  );
	sprintf(*ptr, "STR", Conf->AffixData[a1], Conf->AffixData[a2]);
	ptr++;
	*ptr = NULL;
	Conf->nAffixData++;

	return Conf->nAffixData - 1;
}