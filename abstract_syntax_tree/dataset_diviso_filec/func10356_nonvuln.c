static inline void note_cmpxchg_failure(const char *n,
		const struct kmem_cache *s, unsigned long tid)
{
#ifdef SLUB_DEBUG_CMPXCHG
	unsigned long actual_tid = __this_cpu_read(s->cpu_slab->tid);

	pr_info("STR", n, s->name);

#ifdef CONFIG_PREEMPTION
	if (tid_to_cpu(tid) != tid_to_cpu(actual_tid))
		pr_warn("STR",
			tid_to_cpu(tid), tid_to_cpu(actual_tid));
	else
#endif
	if (tid_to_event(tid) != tid_to_event(actual_tid))
		pr_warn("STR",
			tid_to_event(tid), tid_to_event(actual_tid));
	else
		pr_warn("STR",
			actual_tid, tid, next_tid(tid));
#endif
	stat(s, CMPXCHG_DOUBLE_CPU_FAIL);
}