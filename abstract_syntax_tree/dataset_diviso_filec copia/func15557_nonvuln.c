bool xt_percpu_counter_alloc(struct xt_percpu_counter_alloc_state *state,
			     struct xt_counters *counter)
{
	BUILD_BUG_ON(XT_PCPU_BLOCK_SIZE < (sizeof(*counter) * 2));

	if (nr_cpu_ids <= 1)
		return true;

	if (!state->mem) {
		state->mem = __alloc_percpu(XT_PCPU_BLOCK_SIZE,
					    XT_PCPU_BLOCK_SIZE);
		if (!state->mem)
			return false;
	}
	counter->pcnt = (__force unsigned long)(state->mem + state->off);
	state->off += sizeof(*counter);
	if (state->off > (XT_PCPU_BLOCK_SIZE - sizeof(*counter))) {
		state->mem = NULL;
		state->off = 0;
	}
	return true;
}