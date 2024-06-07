static inline u32 armv8pmu_pmcr_read(void)
{
	u32 val;
	asm volatile("STR" (val));
	return val;
}