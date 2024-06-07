static void * __init pcpu_dfl_fc_alloc(unsigned int cpu, size_t size,
				       size_t align)
{
	return  memblock_virt_alloc_from_nopanic(
			size, align, __pa(MAX_DMA_ADDRESS));
}