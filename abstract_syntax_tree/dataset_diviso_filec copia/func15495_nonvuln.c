int platform_get_irq_byname_optional(struct platform_device *dev,
				     const char *name)
{
	return __platform_get_irq_byname(dev, name);
}