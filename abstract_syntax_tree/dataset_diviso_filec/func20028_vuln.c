static inline void kvm_load_fs(u16 sel)
{
	asm("STR"(sel));
}