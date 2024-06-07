static inline u16 kvm_read_gs(void)
{
	u16 seg;
	asm("STR"(seg));
	return seg;
}