static void bucket_add(struct wdrr_bucket *bucket, struct sk_buff *skb)
{
	if (bucket->head == NULL)
		bucket->head = skb;
	else
		bucket->tail->next = skb;
	bucket->tail = skb;
	skb->next = NULL;
}