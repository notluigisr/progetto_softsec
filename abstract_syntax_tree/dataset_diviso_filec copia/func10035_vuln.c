static inline void vmacache_invalidate(struct mm_struct *mm)
{
	mm->vmacache_seqnum++;

	
	if (unlikely(mm->vmacache_seqnum == 0))
		vmacache_flush_all(mm);
}