int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e)
{
	ptrdiff_t n = (ptrdiff_t)(e - t->table); 

	
	if(n < 0) { return -2; }

	if(t->table[n].k == LH_EMPTY || t->table[n].k == LH_FREED) return -1;
	t->count--;
	if(t->free_fn) t->free_fn(e);
	t->table[n].v = NULL;
	t->table[n].k = LH_FREED;
	if(t->tail == &t->table[n] && t->head == &t->table[n]) {
		t->head = t->tail = NULL;
	} else if (t->head == &t->table[n]) {
		t->head->next->prev = NULL;
		t->head = t->head->next;
	} else if (t->tail == &t->table[n]) {
		t->tail->prev->next = NULL;
		t->tail = t->tail->prev;
	} else {
		t->table[n].prev->next = t->table[n].next;
		t->table[n].next->prev = t->table[n].prev;
	}
	t->table[n].next = t->table[n].prev = NULL;
	return 0;
}