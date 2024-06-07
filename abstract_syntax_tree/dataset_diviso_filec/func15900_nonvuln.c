static inline void slot_queue_init(struct sfq_slot *slot)
{
	memset(slot, 0, sizeof(*slot));
	slot->skblist_prev = slot->skblist_next = (struct sk_buff *)slot;
}