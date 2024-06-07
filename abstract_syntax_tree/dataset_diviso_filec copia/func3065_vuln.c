static struct n_hdlc_buf* n_hdlc_buf_get(struct n_hdlc_buf_list *list)
{
	unsigned long flags;
	struct n_hdlc_buf *buf;
	spin_lock_irqsave(&list->spinlock,flags);
	
	buf = list->head;
	if (buf) {
		list->head = buf->link;
		(list->count)--;
	}
	if (!list->head)
		list->tail = NULL;
	
	spin_unlock_irqrestore(&list->spinlock,flags);
	return buf;
	
}	