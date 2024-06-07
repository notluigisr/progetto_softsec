qf_update_buffer(qf_info_T *qi, qfline_T *old_last)
{
    buf_T	*buf;
    win_T	*win;
    aco_save_T	aco;

    
    buf = qf_find_buf(qi);
    if (buf != NULL)
    {
	linenr_T	old_line_count = buf->b_ml.ml_line_count;
	int		qf_winid = 0;

	if (IS_LL_STACK(qi))
	{
	    if (curwin->w_llist == qi)
		win = curwin;
	    else
	    {
		
		win = qf_find_win_with_loclist(qi);
		if (win == NULL)
		    
		    win = qf_find_win(qi);
		if (win == NULL)
		    return;
	    }
	    qf_winid = win->w_id;
	}

	if (old_last == NULL)
	    
	    aucmd_prepbuf(&aco, buf);

	qf_update_win_titlevar(qi);

	qf_fill_buffer(qf_get_curlist(qi), buf, old_last, qf_winid);
	++CHANGEDTICK(buf);

	if (old_last == NULL)
	{
	    (void)qf_win_pos_update(qi, 0);

	    
	    aucmd_restbuf(&aco);
	}

	
	
	if ((win = qf_find_win(qi)) != NULL && old_line_count < win->w_botline)
	    redraw_buf_later(buf, UPD_NOT_VALID);
    }
}