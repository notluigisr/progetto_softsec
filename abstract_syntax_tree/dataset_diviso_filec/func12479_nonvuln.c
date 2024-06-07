static int xt_jumpstack_alloc(struct xt_table_info *i)
{
	unsigned int size;
	int cpu;

	size = sizeof(void **) * nr_cpu_ids;
	if (size > PAGE_SIZE)
		i->jumpstack = kvzalloc(size, GFP_KERNEL);
	else
		i->jumpstack = kzalloc(size, GFP_KERNEL);
	if (i->jumpstack == NULL)
		return -ENOMEM;

	
	if (i->stacksize == 0)
		return 0;

	
	size = sizeof(void *) * i->stacksize * 2u;
	for_each_possible_cpu(cpu) {
		i->jumpstack[cpu] = kvmalloc_node(size, GFP_KERNEL,
			cpu_to_node(cpu));
		if (i->jumpstack[cpu] == NULL)
			
			return -ENOMEM;
	}

	return 0;
}