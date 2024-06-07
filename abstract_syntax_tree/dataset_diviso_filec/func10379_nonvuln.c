static struct sk_buff *dequeue_head(struct wdrr_bucket *bucket)
{
	struct sk_buff *skb = bucket->head;

	bucket->head = skb->next;
	skb_mark_not_on_list(skb);
	return skb;
}