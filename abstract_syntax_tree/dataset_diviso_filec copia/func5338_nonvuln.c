ex_file(exarg_T *eap)
{
    
    if (eap->addr_count > 0
	    && (*eap->arg != NUL
		|| eap->line2 > 0
		|| eap->addr_count > 1))
    {
	emsg(_(e_invarg));
	return;
    }

    if (*eap->arg != NUL || eap->addr_count == 1)
    {
	if (rename_buffer(eap->arg) == FAIL)
	    return;
	redraw_tabline = TRUE;
    }

    
    if (*eap->arg == NUL || !shortmess(SHM_FILEINFO))
	fileinfo(FALSE, FALSE, eap->forceit);
}