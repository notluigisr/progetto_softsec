static int count_subheaders(struct ctl_table *table)
{
	int has_files = 0;
	int nr_subheaders = 0;
	struct ctl_table *entry;

	
	if (!table || !table->procname)
		return 1;

	for (entry = table; entry->procname; entry++) {
		if (entry->child)
			nr_subheaders += count_subheaders(entry->child);
		else
			has_files = 1;
	}
	return nr_subheaders + has_files;
}