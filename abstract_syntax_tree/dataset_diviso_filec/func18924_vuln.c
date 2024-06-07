static inline void ioat_set_tcp_copy_break(unsigned long copybreak)
{
	#ifdef CONFIG_NET_DMA
	sysctl_tcp_dma_copybreak = copybreak;
	#endif
}