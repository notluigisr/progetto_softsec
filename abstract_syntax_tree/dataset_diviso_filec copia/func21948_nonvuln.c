input_parse_buffer(struct window_pane *wp, u_char *buf, size_t len)
{
	struct input_ctx	*ictx = wp->ictx;
	struct screen_write_ctx	*sctx = &ictx->ctx;

	if (len == 0)
		return;

	window_update_activity(wp->window);
	wp->flags |= PANE_CHANGED;

	
	if (TAILQ_EMPTY(&wp->modes))
		screen_write_start_pane(sctx, wp, &wp->base);
	else
		screen_write_start(sctx, &wp->base);

	log_debug("STR", __func__, wp->id,
	    ictx->state->name, len, (int)len, buf);

	input_parse(ictx, buf, len);
	screen_write_stop(sctx);
}