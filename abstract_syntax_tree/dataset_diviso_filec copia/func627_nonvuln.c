static inline bool __chk_range_not_ok(unsigned long addr, unsigned long size, unsigned long limit)
{
	
	if (__builtin_constant_p(size))
		return unlikely(addr > limit - size);

	
	addr += size;
	if (unlikely(addr < size))
		return true;
	return unlikely(addr > limit);
}