struct cil_list_item *__cil_ordered_find_match(struct cil_list_item *t, struct cil_list_item *i)
{
	while (i) {
		if (i->data == t->data) {
			return i;
		}
		i = i->next;
	}
	return NULL;
}