create_vterm(term_T *term, int rows, int cols)
{
    VTerm	    *vterm;
    VTermScreen	    *screen;
    VTermState	    *state;
    VTermValue	    value;

    vterm = vterm_new_with_allocator(rows, cols, &vterm_allocator, NULL);
    term->tl_vterm = vterm;
    screen = vterm_obtain_screen(vterm);
    vterm_screen_set_callbacks(screen, &screen_callbacks, term);
    
    vterm_set_utf8(vterm, 1);

    init_default_colors(term);

    vterm_state_set_default_colors(
	    vterm_obtain_state(vterm),
	    &term->tl_default_color.fg,
	    &term->tl_default_color.bg);

    if (t_colors >= 16)
	vterm_state_set_bold_highbright(vterm_obtain_state(vterm), 1);

    
    vterm_screen_reset(screen, 1 );

    
    vterm_screen_enable_altscreen(screen, 1);

    
#ifdef WIN3264
    if (GetCaretBlinkTime() == INFINITE)
	value.boolean = 0;
    else
	value.boolean = 1;
#else
    value.boolean = 0;
#endif
    state = vterm_obtain_state(vterm);
    vterm_state_set_termprop(state, VTERM_PROP_CURSORBLINK, &value);
    vterm_state_set_unrecognised_fallbacks(state, &parser_fallbacks, term);
}