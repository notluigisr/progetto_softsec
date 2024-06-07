tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
	tty_add(tty, buf, len);
	if (tty->cx + width > tty->sx) {
		tty->cx = (tty->cx + width) - tty->sx;
		if (tty->cx <= tty->sx)
			tty->cy++;
		else
			tty->cx = tty->cy = UINT_MAX;
	} else
		tty->cx += width;
}