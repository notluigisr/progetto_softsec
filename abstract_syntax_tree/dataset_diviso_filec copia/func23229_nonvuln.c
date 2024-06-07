tty_close(struct tty *tty)
{
	if (event_initialized(&tty->key_timer))
		evtimer_del(&tty->key_timer);
	tty_stop_tty(tty);

	if (tty->flags & TTY_OPENED) {
		evbuffer_free(tty->in);
		event_del(&tty->event_in);
		evbuffer_free(tty->out);
		event_del(&tty->event_out);

		tty_term_free(tty->term);
		tty_keys_free(tty);

		tty->flags &= ~TTY_OPENED;
	}

	if (tty->fd != -1) {
		close(tty->fd);
		tty->fd = -1;
	}
}