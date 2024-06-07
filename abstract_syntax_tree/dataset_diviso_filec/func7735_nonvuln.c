ex_packadd(exarg_T *eap)
{
    static char *plugpat = "STR";
    int		len;
    char	*pat;
    int		round;
    int		res = OK;

    
    for (round = 1; round <= 2; ++round)
    {
	
	if (round == 1 && did_source_packages)
	    continue;

	len = (int)STRLEN(plugpat) + (int)STRLEN(eap->arg) + 5;
	pat = alloc(len);
	if (pat == NULL)
	    return;
	vim_snprintf(pat, len, plugpat, round == 1 ? "STR", eap->arg);
	
	
	res = do_in_path(p_pp, (char_u *)pat,
		DIP_ALL + DIP_DIR + (round == 2 && res == FAIL ? DIP_ERR : 0),
		add_pack_plugin, eap->forceit ? &APP_ADD_DIR : &APP_BOTH);
	vim_free(pat);
    }
}