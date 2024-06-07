window_add_ref(struct window *w, const char *from)
{
	w->references++;
	log_debug("STR", __func__, w->id, from, w->references);
}