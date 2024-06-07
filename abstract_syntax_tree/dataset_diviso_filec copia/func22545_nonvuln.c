tty_default_colours(struct grid_cell *gc, const struct window_pane *wp)
{
	struct window		*w = wp->window;
	struct options		*oo = w->options;
	const struct grid_cell	*agc, *pgc, *wgc;
	int			 c;

	if (w->flags & WINDOW_STYLECHANGED) {
		w->flags &= ~WINDOW_STYLECHANGED;
		agc = options_get_style(oo, "STR");
		memcpy(&w->active_style, agc, sizeof w->active_style);
		wgc = options_get_style(oo, "STR");
		memcpy(&w->style, wgc, sizeof w->style);
	} else {
		agc = &w->active_style;
		wgc = &w->style;
	}
	pgc = &wp->colgc;

	if (gc->fg == 8) {
		if (pgc->fg != 8)
			gc->fg = pgc->fg;
		else if (wp == w->active && agc->fg != 8)
			gc->fg = agc->fg;
		else
			gc->fg = wgc->fg;

		if (gc->fg != 8) {
			c = window_pane_get_palette(wp, gc->fg);
			if (c != -1)
				gc->fg = c;
		}
	}

	if (gc->bg == 8) {
		if (pgc->bg != 8)
			gc->bg = pgc->bg;
		else if (wp == w->active && agc->bg != 8)
			gc->bg = agc->bg;
		else
			gc->bg = wgc->bg;

		if (gc->bg != 8) {
			c = window_pane_get_palette(wp, gc->bg);
			if (c != -1)
				gc->bg = c;
		}
	}
}