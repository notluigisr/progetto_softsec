int tls1_set_sigalgs_list(CERT *c, const char *str)
	{
	sig_cb_st sig;
	sig.sigalgcnt = 0;
	if (!CONF_parse_list(str, ':', 1, sig_cb, &sig))
		return 0;
	return tls1_set_sigalgs(c, sig.sigalgs, sig.sigalgcnt);
	}