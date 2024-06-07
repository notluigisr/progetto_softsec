int tty_prepare_flip_string(struct tty_struct *tty, unsigned char **chars,
								size_t size)
{
	int space;
	unsigned long flags;
	struct tty_buffer *tb;

	spin_lock_irqsave(&tty->buf.lock, flags);
	space = __tty_buffer_request_room(tty, size);

	tb = tty->buf.tail;
	if (likely(space)) {
		*chars = tb->char_buf_ptr + tb->used;
		memset(tb->flag_buf_ptr + tb->used, TTY_NORMAL, space);
		tb->used += space;
	}
	spin_unlock_irqrestore(&tty->buf.lock, flags);
	return space;
}