win_size_restore(garray_T *gap)
{
    win_T	*wp;
    int		i, j;

    if (win_count() * 2 == gap->ga_len)
    {
	
	for (j = 0; j < 2; ++j)
	{
	    i = 0;
	    FOR_ALL_WINDOWS(wp)
	    {
		frame_setwidth(wp->w_frame, ((int *)gap->ga_data)[i++]);
		win_setheight_win(((int *)gap->ga_data)[i++], wp);
	    }
	}
	
	(void)win_comp_pos();
    }
}