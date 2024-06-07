store_word(
    spellinfo_T	*spin,
    char_u	*word,
    int		flags,		
    int		region,		
    char_u	*pfxlist,	
    int		need_affix)	
{
    int		len = (int)STRLEN(word);
    int		ct = captype(word, word + len);
    char_u	foldword[MAXWLEN];
    int		res = OK;
    char_u	*p;

    
    if (enc_utf8 && !utf_valid_string(word, NULL))
	return FAIL;

    (void)spell_casefold(curwin, word, len, foldword, MAXWLEN);
    for (p = pfxlist; res == OK; ++p)
    {
	if (!need_affix || (p != NULL && *p != NUL))
	    res = tree_add_word(spin, foldword, spin->si_foldroot, ct | flags,
						  region, p == NULL ? 0 : *p);
	if (p == NULL || *p == NUL)
	    break;
    }
    ++spin->si_foldwcount;

    if (res == OK && (ct == WF_KEEPCAP || (flags & WF_KEEPCAP)))
    {
	for (p = pfxlist; res == OK; ++p)
	{
	    if (!need_affix || (p != NULL && *p != NUL))
		res = tree_add_word(spin, word, spin->si_keeproot, flags,
						  region, p == NULL ? 0 : *p);
	    if (p == NULL || *p == NUL)
		break;
	}
	++spin->si_keepwcount;
    }
    return res;
}