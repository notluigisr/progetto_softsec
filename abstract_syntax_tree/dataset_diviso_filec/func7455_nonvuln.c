static int mbochs_get_irq_info(struct vfio_irq_info *irq_info)
{
	irq_info->count = 0;
	return 0;
}