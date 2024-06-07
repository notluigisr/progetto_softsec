megasas_disable_intr_gen2(struct megasas_instance *instance)
{
	struct megasas_register_set __iomem *regs;
	u32 mask = 0xFFFFFFFF;

	regs = instance->reg_set;
	writel(mask, &regs->outbound_intr_mask);
	
	readl(&regs->outbound_intr_mask);
}