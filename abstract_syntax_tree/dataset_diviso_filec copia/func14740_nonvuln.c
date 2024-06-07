may_set_cursor_props(term_T *term)
{
#ifdef FEAT_GUI
    
    if (gui.in_use)
	return;
#endif
    if (in_terminal_loop == term)
    {
	cursor_color_copy(&desired_cursor_color, term->tl_cursor_color);
	desired_cursor_shape = term->tl_cursor_shape;
	desired_cursor_blink = term->tl_cursor_blink;
	may_output_cursor_props();
    }
}