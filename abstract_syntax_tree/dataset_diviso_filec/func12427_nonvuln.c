static int do_page_mkwrite(struct vm_area_struct *vma, struct page *page,
	       unsigned long address)
{
	struct vm_fault vmf;
	int ret;

	vmf.virtual_address = (void __user *)(address & PAGE_MASK);
	vmf.pgoff = page->index;
	vmf.flags = FAULT_FLAG_WRITE|FAULT_FLAG_MKWRITE;
	vmf.page = page;
	vmf.cow_page = NULL;

	ret = vma->vm_ops->page_mkwrite(vma, &vmf);
	if (unlikely(ret & (VM_FAULT_ERROR | VM_FAULT_NOPAGE)))
		return ret;
	if (unlikely(!(ret & VM_FAULT_LOCKED))) {
		lock_page(page);
		if (!page->mapping) {
			unlock_page(page);
			return 0; 
		}
		ret |= VM_FAULT_LOCKED;
	} else
		VM_BUG_ON_PAGE(!PageLocked(page), page);
	return ret;
}