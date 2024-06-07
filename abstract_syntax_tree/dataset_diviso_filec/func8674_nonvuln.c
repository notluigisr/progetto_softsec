ebt_check_entry_size_and_hooks(const struct ebt_entry *e,
			       const struct ebt_table_info *newinfo,
			       unsigned int *n, unsigned int *cnt,
			       unsigned int *totalcnt, unsigned int *udc_cnt)
{
	int i;

	for (i = 0; i < NF_BR_NUMHOOKS; i++) {
		if ((void *)e == (void *)newinfo->hook_entry[i])
			break;
	}
	
	if (i != NF_BR_NUMHOOKS || !e->bitmask) {
		
		if (*n != *cnt) {
			BUGPRINT("STR"
				 "STR");
			return -EINVAL;
		}
		if (((struct ebt_entries *)e)->policy != EBT_DROP &&
		   ((struct ebt_entries *)e)->policy != EBT_ACCEPT) {
			
			if (i != NF_BR_NUMHOOKS ||
			   ((struct ebt_entries *)e)->policy != EBT_RETURN) {
				BUGPRINT("STR");
				return -EINVAL;
			}
		}
		if (i == NF_BR_NUMHOOKS) 
			(*udc_cnt)++;
		if (((struct ebt_entries *)e)->counter_offset != *totalcnt) {
			BUGPRINT("STR");
			return -EINVAL;
		}
		*n = ((struct ebt_entries *)e)->nentries;
		*cnt = 0;
		return 0;
	}
	
	if (sizeof(struct ebt_entry) > e->watchers_offset ||
	   e->watchers_offset > e->target_offset ||
	   e->target_offset >= e->next_offset) {
		BUGPRINT("STR");
		return -EINVAL;
	}
	
	if (e->next_offset - e->target_offset < sizeof(struct ebt_entry_target)) {
		BUGPRINT("STR");
		return -EINVAL;
	}
	(*cnt)++;
	(*totalcnt)++;
	return 0;
}