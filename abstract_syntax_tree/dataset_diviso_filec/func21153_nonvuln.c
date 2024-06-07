tty_set_title(struct tty *tty, const char *title)
{
	if (!tty_term_has(tty->term, TTYC_TSL) ||
	    !tty_term_has(tty->term, TTYC_FSL))
		return;

	tty_putcode(tty, TTYC_TSL);
	tty_puts(tty, title);
	tty_putcode(tty, TTYC_FSL);
}