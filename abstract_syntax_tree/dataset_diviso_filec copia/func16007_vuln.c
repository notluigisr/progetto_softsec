static unsigned long mmap_rnd(void)
{
	unsigned long rnd = 0;

	if (current->flags & PF_RANDOMIZE) {
		
		if (is_32bit_task())
			rnd = (long)(get_random_int() % (1<<(23-PAGE_SHIFT)));
		else
			rnd = (long)(get_random_int() % (1<<(30-PAGE_SHIFT)));
	}
	return rnd << PAGE_SHIFT;
}