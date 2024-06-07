static struct sctp_ulpevent *sctp_make_reassembled_event(struct sk_buff_head *queue, struct sk_buff *f_frag, struct sk_buff *l_frag)
{
	struct sk_buff *pos;
	struct sctp_ulpevent *event;
	struct sk_buff *pnext, *last;
	struct sk_buff *list = skb_shinfo(f_frag)->frag_list;

	
	if (f_frag == l_frag)
		pos = NULL;
	else
		pos = f_frag->next;

	
	for (last = list; list; last = list, list = list->next);

	
	if (last)
		last->next = pos;
	else
		skb_shinfo(f_frag)->frag_list = pos;

	
	__skb_unlink(f_frag, queue);
	while (pos) {

		pnext = pos->next;

		
		f_frag->len += pos->len;
		f_frag->data_len += pos->len;

		
		__skb_unlink(pos, queue);
	
		
		if (pos == l_frag)
			break;
		pos->next = pnext;
		pos = pnext;
	};

	event = sctp_skb2event(f_frag);
	SCTP_INC_STATS(SCTP_MIB_REASMUSRMSGS);

	return event;
}