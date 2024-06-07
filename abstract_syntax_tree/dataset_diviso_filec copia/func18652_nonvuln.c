int xt_register_table(struct xt_table *table,
		      struct xt_table_info *bootstrap,
		      struct xt_table_info *newinfo)
{
	int ret;
	struct xt_table_info *private;
	struct xt_table *t;

	ret = mutex_lock_interruptible(&xt[table->af].mutex);
	if (ret != 0)
		return ret;

	
	list_for_each_entry(t, &xt[table->af].tables, list) {
		if (strcmp(t->name, table->name) == 0) {
			ret = -EEXIST;
			goto unlock;
		}
	}

	
	table->private = bootstrap;
	rwlock_init(&table->lock);
	if (!xt_replace_table(table, 0, newinfo, &ret))
		goto unlock;

	private = table->private;
	duprintf("STR", private->number);

	
	private->initial_entries = private->number;

	list_add(&table->list, &xt[table->af].tables);

	ret = 0;
 unlock:
	mutex_unlock(&xt[table->af].mutex);
	return ret;
}