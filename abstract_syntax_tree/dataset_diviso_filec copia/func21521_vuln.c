void uprobe_dup_mmap(struct mm_struct *oldmm, struct mm_struct *newmm)
{
	newmm->uprobes_state.xol_area = NULL;

	if (test_bit(MMF_HAS_UPROBES, &oldmm->flags)) {
		set_bit(MMF_HAS_UPROBES, &newmm->flags);
		
		set_bit(MMF_RECALC_UPROBES, &newmm->flags);
	}
}