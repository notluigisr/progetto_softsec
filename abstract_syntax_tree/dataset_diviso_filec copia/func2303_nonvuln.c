term_channel_closed(channel_T *ch)
{
    term_T *term;
    term_T *next_term;
    int	    did_one = FALSE;

    for (term = first_term; term != NULL; term = next_term)
    {
	next_term = term->tl_next;
	if (term->tl_job == ch->ch_job)
	{
	    term->tl_channel_closed = TRUE;
	    did_one = TRUE;

	    VIM_CLEAR(term->tl_title);
	    VIM_CLEAR(term->tl_status_text);
#ifdef WIN3264
	    if (term->tl_out_fd != NULL)
	    {
		fclose(term->tl_out_fd);
		term->tl_out_fd = NULL;
	    }
#endif

	    if (updating_screen)
	    {
		
		term->tl_channel_recently_closed = TRUE;
		continue;
	    }

	    if (term_after_channel_closed(term))
		next_term = first_term;
	}
    }

    if (did_one)
    {
	redraw_statuslines();

	
	ins_char_typebuf(K_IGNORE);
	typebuf_was_filled = TRUE;

	term = curbuf->b_term;
	if (term != NULL)
	{
	    if (term->tl_job == ch->ch_job)
		maketitle();
	    update_cursor(term, term->tl_cursor_visible);
	}
    }
}