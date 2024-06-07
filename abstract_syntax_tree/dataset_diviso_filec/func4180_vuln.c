int tty_buffer_request_room(struct tty_struct *tty, size_t size)
{
	struct tty_buffer *b, *n;
	int left;
	unsigned long flags;

	spin_lock_irqsave(&tty->buf.lock, flags);

	
	if ((b = tty->buf.tail) != NULL)
		left = b->size - b->used;
	else
		left = 0;

	if (left < size) {
		
		if ((n = tty_buffer_find(tty, size)) != NULL) {
			if (b != NULL) {
				b->next = n;
				b->commit = b->used;
			} else
				tty->buf.head = n;
			tty->buf.tail = n;
		} else
			size = left;
	}

	spin_unlock_irqrestore(&tty->buf.lock, flags);
	return size;
}