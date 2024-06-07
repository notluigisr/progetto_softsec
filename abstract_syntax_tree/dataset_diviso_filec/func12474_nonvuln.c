window_redraw_active_switch(struct window *w, struct window_pane *wp)
{
	const struct grid_cell	*gc;

	if (wp == w->active)
		return;

	
	gc = options_get_style(w->options, "STR");
	if (style_equal(gc, options_get_style(w->options, "STR")))
		return;

	
	if (window_pane_get_palette(w->active, w->active->colgc.fg) != -1 ||
	    window_pane_get_palette(w->active, w->active->colgc.bg) != -1 ||
	    style_equal(&grid_default_cell, &w->active->colgc))
		w->active->flags |= PANE_REDRAW;
	if (window_pane_get_palette(wp, wp->colgc.fg) != -1 ||
	    window_pane_get_palette(wp, wp->colgc.bg) != -1 ||
	    style_equal(&grid_default_cell, &wp->colgc))
		wp->flags |= PANE_REDRAW;
}