win_alloc_popup_win(void)
{
    win_T *wp;

    wp = win_alloc(NULL, TRUE);
    if (wp != NULL)
    {
	
	
	win_init_some(wp, curwin);

	RESET_BINDING(wp);
	new_frame(wp);
    }
    return wp;
}