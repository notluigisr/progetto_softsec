goto_tabpage_tp(
    tabpage_T	*tp,
    int		trigger_enter_autocmds,
    int		trigger_leave_autocmds)
{
    
    set_keep_msg(NULL, 0);

    if (tp != curtab && leave_tabpage(tp->tp_curwin->w_buffer,
					trigger_leave_autocmds) == OK)
    {
	if (valid_tabpage(tp))
	    enter_tabpage(tp, curbuf, trigger_enter_autocmds,
		    trigger_leave_autocmds);
	else
	    enter_tabpage(curtab, curbuf, trigger_enter_autocmds,
		    trigger_leave_autocmds);
    }
}