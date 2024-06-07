static inline void kvm_load_gs(u16 sel)
{
	asm("STR"(sel));
}