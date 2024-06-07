window_set_active_pane(struct window *w, struct window_pane *wp)
{
	log_debug("STR", __func__, wp->id, w->active->id);
	if (wp == w->active)
		return (0);
	w->last = w->active;
	w->active = wp;
	w->active->active_point = next_active_point++;
	w->active->flags |= PANE_CHANGED;
	tty_update_window_offset(w);
	notify_window("STR", w);
	return (1);
}