static int amd_gpio_direction_output(struct gpio_chip *gc, unsigned offset,
		int value)
{
	u32 pin_reg;
	unsigned long flags;
	struct amd_gpio *gpio_dev = gpiochip_get_data(gc);

	spin_lock_irqsave(&gpio_dev->lock, flags);
	pin_reg = readl(gpio_dev->base + offset * 4);
	pin_reg |= BIT(OUTPUT_ENABLE_OFF);
	if (value)
		pin_reg |= BIT(OUTPUT_VALUE_OFF);
	else
		pin_reg &= ~BIT(OUTPUT_VALUE_OFF);
	writel(pin_reg, gpio_dev->base + offset * 4);
	spin_unlock_irqrestore(&gpio_dev->lock, flags);

	return 0;
}