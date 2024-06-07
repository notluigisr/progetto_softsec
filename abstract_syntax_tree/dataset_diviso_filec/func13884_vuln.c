win_new_tabpage(int after)
{
    tabpage_T	*tp = curtab;
    tabpage_T	*prev_tp = curtab;
    tabpage_T	*newtp;
    int		n;

    newtp = alloc_tabpage();
    if (newtp == NULL)
	return FAIL;

    
    if (leave_tabpage(curbuf, TRUE) == FAIL)
    {
	vim_free(newtp);
	return FAIL;
    }
    curtab = newtp;

    newtp->tp_localdir = (tp->tp_localdir == NULL)
				    ? NULL : vim_strsave(tp->tp_localdir);
    
    if (win_alloc_firstwin(tp->tp_curwin) == OK)
    {
	
	if (after == 1)
	{
	    
	    newtp->tp_next = first_tabpage;
	    first_tabpage = newtp;
	}
	else
	{
	    if (after > 0)
	    {
		
		n = 2;
		for (tp = first_tabpage; tp->tp_next != NULL
					       && n < after; tp = tp->tp_next)
		    ++n;
	    }
	    newtp->tp_next = tp->tp_next;
	    tp->tp_next = newtp;
	}
	newtp->tp_firstwin = newtp->tp_lastwin = newtp->tp_curwin = curwin;

	win_init_size();
	firstwin->w_winrow = tabline_height();
	win_comp_scroll(curwin);

	newtp->tp_topframe = topframe;
	last_status(FALSE);

	lastused_tabpage = prev_tp;

#if defined(FEAT_GUI)
	
	
	gui_may_update_scrollbars();
#endif
#ifdef FEAT_JOB_CHANNEL
	entering_window(curwin);
#endif

	redraw_all_later(NOT_VALID);
	apply_autocmds(EVENT_WINNEW, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_WINENTER, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_TABNEW, NULL, NULL, FALSE, curbuf);
	apply_autocmds(EVENT_TABENTER, NULL, NULL, FALSE, curbuf);
	return OK;
    }

    
    enter_tabpage(curtab, curbuf, TRUE, TRUE);
    return FAIL;
}