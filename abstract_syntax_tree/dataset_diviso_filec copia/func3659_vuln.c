tlb_update_vma_flags(struct mmu_gather *tlb, struct vm_area_struct *vma)
{
	
	tlb->vma_huge = is_vm_hugetlb_page(vma);
	tlb->vma_exec = !!(vma->vm_flags & VM_EXEC);
}