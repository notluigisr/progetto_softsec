static struct entry *tstat_lookup(struct entry *entry, char *comm)
{
	struct entry **head, *curr, *prev;

	head = tstat_hashentry(entry);
	curr = *head;

	
	while (curr) {
		if (match_entries(curr, entry))
			return curr;

		curr = curr->next;
	}
	
	prev = NULL;
	curr = *head;

	raw_spin_lock(&table_lock);
	
	while (curr) {
		if (match_entries(curr, entry))
			goto out_unlock;

		prev = curr;
		curr = curr->next;
	}

	curr = alloc_entry();
	if (curr) {
		*curr = *entry;
		curr->count = 0;
		curr->next = NULL;
		memcpy(curr->comm, comm, TASK_COMM_LEN);

		smp_mb(); 

		if (prev)
			prev->next = curr;
		else
			*head = curr;
	}
 out_unlock:
	raw_spin_unlock(&table_lock);

	return curr;
}