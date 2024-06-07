input_set_state(struct window_pane *wp, const struct input_transition *itr)
{
	struct input_ctx	*ictx = wp->ictx;

	if (ictx->state->exit != NULL)
		ictx->state->exit(ictx);
	ictx->state = itr->state;
	if (ictx->state->enter != NULL)
		ictx->state->enter(ictx);
}