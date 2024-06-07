check_secure(void)
{
    if (secure)
    {
	secure = 2;
	emsg(_(e_curdir));
	return TRUE;
    }
#ifdef HAVE_SANDBOX
    
    if (sandbox != 0)
    {
	emsg(_(e_sandbox));
	return TRUE;
    }
#endif
    return FALSE;
}