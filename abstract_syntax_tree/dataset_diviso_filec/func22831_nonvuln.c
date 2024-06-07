entering_window(win_T *win)
{
    
    if (!bt_prompt(win->w_buffer))
	return;

    
    
    if (win->w_buffer->b_prompt_insert != NUL)
	stop_insert_mode = FALSE;

    
    
    if ((State & MODE_INSERT) == 0)
	restart_edit = win->w_buffer->b_prompt_insert;
}