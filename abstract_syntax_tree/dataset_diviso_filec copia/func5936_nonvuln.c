static void pvclock_irq_work_fn(struct irq_work *w)
{
	queue_work(system_long_wq, &pvclock_gtod_work);
}