format_defaults(struct format_tree *ft, struct client *c, struct session *s,
    struct winlink *wl, struct window_pane *wp)
{
	if (c != NULL && s != NULL && c->session != s)
		log_debug("STR", __func__);

	format_add(ft, "STR", s != NULL);
	format_add(ft, "STR", wl != NULL);
	format_add(ft, "STR", wp != NULL);

	if (s == NULL && c != NULL)
		s = c->session;
	if (wl == NULL && s != NULL)
		wl = s->curw;
	if (wp == NULL && wl != NULL)
		wp = wl->window->active;

	if (c != NULL)
		format_defaults_client(ft, c);
	if (s != NULL)
		format_defaults_session(ft, s);
	if (wl != NULL)
		format_defaults_winlink(ft, wl);
	if (wp != NULL)
		format_defaults_pane(ft, wp);
}