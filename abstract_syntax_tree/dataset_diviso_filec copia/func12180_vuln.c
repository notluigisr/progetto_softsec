goto_tabpage(int n)
{
    tabpage_T	*tp = NULL;  
    tabpage_T	*ttp;
    int		i;

    if (text_locked())
    {
	
	text_locked_msg();
	return;
    }

    
    if (first_tabpage->tp_next == NULL)
    {
	if (n > 1)
	    beep_flush();
	return;
    }

    if (n == 0)
    {
	
	if (curtab->tp_next == NULL)
	    tp = first_tabpage;
	else
	    tp = curtab->tp_next;
    }
    else if (n < 0)
    {
	
	
	ttp = curtab;
	for (i = n; i < 0; ++i)
	{
	    for (tp = first_tabpage; tp->tp_next != ttp && tp->tp_next != NULL;
		    tp = tp->tp_next)
		;
	    ttp = tp;
	}
    }
    else if (n == 9999)
    {
	
	for (tp = first_tabpage; tp->tp_next != NULL; tp = tp->tp_next)
	    ;
    }
    else
    {
	
	tp = find_tabpage(n);
	if (tp == NULL)
	{
	    beep_flush();
	    return;
	}
    }

    goto_tabpage_tp(tp, TRUE, TRUE);

#ifdef FEAT_GUI_TABLINE
    if (gui_use_tabline())
	gui_mch_set_curtab(tabpage_index(curtab));
#endif
}