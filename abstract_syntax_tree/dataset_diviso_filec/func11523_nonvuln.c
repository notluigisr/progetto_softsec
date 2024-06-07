	__releases(vmf->ptl)
{
	struct vm_area_struct *vma = vmf->vma;

	get_page(vmf->page);

	if (vma->vm_ops && vma->vm_ops->page_mkwrite) {
		int tmp;

		pte_unmap_unlock(vmf->pte, vmf->ptl);
		tmp = do_page_mkwrite(vmf);
		if (unlikely(!tmp || (tmp &
				      (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))) {
			put_page(vmf->page);
			return tmp;
		}
		tmp = finish_mkwrite_fault(vmf);
		if (unlikely(tmp & (VM_FAULT_ERROR | VM_FAULT_NOPAGE))) {
			unlock_page(vmf->page);
			put_page(vmf->page);
			return tmp;
		}
	} else {
		wp_page_reuse(vmf);
		lock_page(vmf->page);
	}
	fault_dirty_shared_page(vma, vmf->page);
	put_page(vmf->page);

	return VM_FAULT_WRITE;
}