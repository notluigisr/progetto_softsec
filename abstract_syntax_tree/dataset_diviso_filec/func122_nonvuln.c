static inline unsigned int xt_write_recseq_begin(void)
{
	unsigned int addend;

	
	addend = (__this_cpu_read(xt_recseq.sequence) + 1) & 1;

	
	__this_cpu_add(xt_recseq.sequence, addend);
	smp_mb();

	return addend;
}