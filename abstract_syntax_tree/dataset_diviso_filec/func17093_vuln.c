static unsigned long mmap_rnd(void)
{
	unsigned long rnd = 0UL;

	if (current->flags & PF_RANDOMIZE) {
		unsigned long val = get_random_int();
		if (test_thread_flag(TIF_32BIT))
			rnd = (val % (1UL << (22UL-PAGE_SHIFT)));
		else
			rnd = (val % (1UL << (29UL-PAGE_SHIFT)));
	}
	return (rnd << PAGE_SHIFT) * 2;
}