static inline int empty_stack(void)
{
	return gc_current == GC_HEAD;
}