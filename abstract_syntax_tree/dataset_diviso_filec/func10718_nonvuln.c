shell_new_rows(void)
{
    int		h = (int)ROWS_AVAIL;

    if (firstwin == NULL)	
	return;
    if (h < frame_minheight(topframe, NULL))
	h = frame_minheight(topframe, NULL);

    
    frame_new_height(topframe, h, FALSE, TRUE);
    if (!frame_check_height(topframe, h))
	frame_new_height(topframe, h, FALSE, FALSE);

    (void)win_comp_pos();		
    compute_cmdrow();
    curtab->tp_ch_used = p_ch;

#if 0
    
    if (p_ea)
	win_equal(curwin, FALSE, 'v');
#endif
}