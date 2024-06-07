win_setwidth_win(int width, win_T *wp)
{
    
    
    if (wp == curwin)
    {
	if (width < p_wmw)
	    width = p_wmw;
	if (width == 0)
	    width = 1;
    }
    else if (width < 0)
	width = 0;

    frame_setwidth(wp->w_frame, width + wp->w_vsep_width);

    
    (void)win_comp_pos();

    redraw_all_later(NOT_VALID);
}