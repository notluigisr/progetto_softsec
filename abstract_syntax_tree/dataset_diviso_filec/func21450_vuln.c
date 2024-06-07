static inline int check_entry_size_and_hooks(struct arpt_entry *e,
					     struct xt_table_info *newinfo,
					     const unsigned char *base,
					     const unsigned char *limit,
					     const unsigned int *hook_entries,
					     const unsigned int *underflows,
					     unsigned int valid_hooks)
{
	unsigned int h;

	if ((unsigned long)e % __alignof__(struct arpt_entry) != 0 ||
	    (unsigned char *)e + sizeof(struct arpt_entry) >= limit) {
		duprintf("STR", e);
		return -EINVAL;
	}

	if (e->next_offset
	    < sizeof(struct arpt_entry) + sizeof(struct xt_entry_target)) {
		duprintf("STR",
			 e, e->next_offset);
		return -EINVAL;
	}

	
	for (h = 0; h < NF_ARP_NUMHOOKS; h++) {
		if (!(valid_hooks & (1 << h)))
			continue;
		if ((unsigned char *)e - base == hook_entries[h])
			newinfo->hook_entry[h] = hook_entries[h];
		if ((unsigned char *)e - base == underflows[h]) {
			if (!check_underflow(e)) {
				pr_err("STR"
				       "STR"
				       "STR");
				return -EINVAL;
			}
			newinfo->underflow[h] = underflows[h];
		}
	}

	
	e->counters = ((struct xt_counters) { 0, 0 });
	e->comefrom = 0;
	return 0;
}