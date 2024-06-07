aubuflocal_remove(buf_T *buf)
{
    AutoPat	*ap;
    event_T	event;
    AutoPatCmd	*apc;

    
    for (apc = active_apc_list; apc; apc = apc->next)
	if (buf->b_fnum == apc->arg_bufnr)
	    apc->arg_bufnr = 0;

    
    for (event = (event_T)0; (int)event < (int)NUM_EVENTS;
					    event = (event_T)((int)event + 1))
	
	for (ap = first_autopat[(int)event]; ap != NULL; ap = ap->next)
	    if (ap->buflocal_nr == buf->b_fnum)
	    {
		au_remove_pat(ap);
		if (p_verbose >= 6)
		{
		    verbose_enter();
		    smsg((char_u *)
			    _("STR"),
					   event_nr2name(event), buf->b_fnum);
		    verbose_leave();
		}
	    }
    au_cleanup();
}