prepare_tagpreview(
    int		undo_sync)	
{
    win_T	*wp;

# ifdef FEAT_GUI
    need_mouse_correct = TRUE;
# endif

    
    if (!curwin->w_p_pvw)
    {
	FOR_ALL_WINDOWS(wp)
	    if (wp->w_p_pvw)
		break;
	if (wp != NULL)
	    win_enter(wp, undo_sync);
	else
	{
	    
	    if (win_split(g_do_tagpreview > 0 ? g_do_tagpreview : 0, 0)
								      == FAIL)
		return FALSE;
	    curwin->w_p_pvw = TRUE;
	    curwin->w_p_wfh = TRUE;
	    RESET_BINDING(curwin);	    
# ifdef FEAT_DIFF
	    curwin->w_p_diff = FALSE;	    
# endif
# ifdef FEAT_FOLDING
	    curwin->w_p_fdc = 0;	    
# endif
	    return TRUE;
	}
    }
    return FALSE;
}