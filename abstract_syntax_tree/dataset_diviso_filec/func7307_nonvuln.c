hgr_get_ll(int *new_ll)
{
    win_T	*wp;
    qf_info_T	*qi;

    
    if (bt_help(curwin->w_buffer))
	wp = curwin;
    else
	
	wp = qf_find_help_win();

    if (wp == NULL)	    
	qi = NULL;
    else
	qi = wp->w_llist;

    if (qi == NULL)
    {
	
	if ((qi = qf_alloc_stack(QFLT_LOCATION)) == NULL)
	    return NULL;
	*new_ll = TRUE;
    }

    return qi;
}