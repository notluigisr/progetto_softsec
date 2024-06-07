static struct ea_list *ea_list_union(struct ea_list *name_list, struct ea_list *file_list, size_t *total_ea_len)
{
	struct ea_list *nlistp, *flistp;

	for (nlistp = name_list; nlistp; nlistp = nlistp->next) {
		for (flistp = file_list; flistp; flistp = flistp->next) {
			if (strequal(nlistp->ea.name, flistp->ea.name)) {
				break;
			}
		}

		if (flistp) {
			
			nlistp->ea.flags = flistp->ea.flags;
			nlistp->ea.value = flistp->ea.value;
		} else {
			
			nlistp->ea.flags = 0;
			ZERO_STRUCT(nlistp->ea.value);
		}
	}

	*total_ea_len = ea_list_size(name_list);
	return name_list;
}