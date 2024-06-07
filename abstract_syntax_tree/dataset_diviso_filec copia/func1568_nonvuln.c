static u64 get_coherent_dma_mask(struct device *dev)
{
	u64 mask = (u64)arm_dma_limit;

	if (dev) {
		mask = dev->coherent_dma_mask;

		
		if (mask == 0) {
			dev_warn(dev, "STR");
			return 0;
		}

		if ((~mask) & (u64)arm_dma_limit) {
			dev_warn(dev, "STR"
				 "STR",
				 mask, (u64)arm_dma_limit);
			return 0;
		}
	}

	return mask;
}