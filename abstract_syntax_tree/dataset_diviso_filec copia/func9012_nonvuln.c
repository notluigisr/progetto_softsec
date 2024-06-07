int tty_insert_flip_string_flags(struct tty_struct *tty,
		const unsigned char *chars, const char *flags, size_t size)
{
	int copied = 0;
	do {
		int goal = min_t(size_t, size - copied, TTY_BUFFER_PAGE);
		int space;
		unsigned long __flags;
		struct tty_buffer *tb;

		spin_lock_irqsave(&tty->buf.lock, __flags);
		space = __tty_buffer_request_room(tty, goal);
		tb = tty->buf.tail;
		
		if (unlikely(space == 0)) {
			spin_unlock_irqrestore(&tty->buf.lock, __flags);
			break;
		}
		memcpy(tb->char_buf_ptr + tb->used, chars, space);
		memcpy(tb->flag_buf_ptr + tb->used, flags, space);
		tb->used += space;
		spin_unlock_irqrestore(&tty->buf.lock, __flags);
		copied += space;
		chars += space;
		flags += space;
		
	} while (unlikely(size > copied));
	return copied;
}