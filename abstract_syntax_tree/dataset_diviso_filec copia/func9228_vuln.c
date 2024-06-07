static void xen_irq_init(unsigned irq)
{
	struct irq_info *info;
#ifdef CONFIG_SMP
	
	cpumask_copy(irq_get_affinity_mask(irq), cpumask_of(0));
#endif

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		panic("STR", irq);

	info->type = IRQT_UNBOUND;
	info->refcnt = -1;

	set_info_for_irq(irq, info);

	list_add_tail(&info->list, &xen_irq_list_head);
}