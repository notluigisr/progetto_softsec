static void get_counters(const struct xt_table_info *t,
			 struct xt_counters counters[])
{
	struct arpt_entry *iter;
	unsigned int cpu;
	unsigned int i;

	for_each_possible_cpu(cpu) {
		seqlock_t *lock = &per_cpu(xt_info_locks, cpu).lock;

		i = 0;
		xt_entry_foreach(iter, t->entries[cpu], t->size) {
			u64 bcnt, pcnt;
			unsigned int start;

			do {
				start = read_seqbegin(lock);
				bcnt = iter->counters.bcnt;
				pcnt = iter->counters.pcnt;
			} while (read_seqretry(lock, start));

			ADD_COUNTER(counters[i], bcnt, pcnt);
			++i;
		}
	}
}