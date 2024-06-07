static void check_stack_usage(void)
{
	static DEFINE_SPINLOCK(low_water_lock);
	static int lowest_to_date = THREAD_SIZE;
	unsigned long *n = end_of_stack(current);
	unsigned long free;

	while (*n == 0)
		n++;
	free = (unsigned long)n - (unsigned long)end_of_stack(current);

	if (free >= lowest_to_date)
		return;

	spin_lock(&low_water_lock);
	if (free < lowest_to_date) {
		printk(KERN_WARNING "STR"
				"STR",
				current->comm, free);
		lowest_to_date = free;
	}
	spin_unlock(&low_water_lock);
}