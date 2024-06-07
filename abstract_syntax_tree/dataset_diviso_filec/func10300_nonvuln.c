static inline bool mmget_still_valid(struct mm_struct *mm)
{
	return likely(!mm->core_state);
}