radix__hugetlb_get_unmapped_area(struct file *file, unsigned long addr,
				unsigned long len, unsigned long pgoff,
				unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	struct hstate *h = hstate_file(file);
	struct vm_unmapped_area_info info;

	if (unlikely(addr > mm->context.addr_limit && addr < TASK_SIZE))
		mm->context.addr_limit = TASK_SIZE;

	if (len & ~huge_page_mask(h))
		return -EINVAL;
	if (len > mm->task_size)
		return -ENOMEM;

	if (flags & MAP_FIXED) {
		if (prepare_hugepage_range(file, addr, len))
			return -EINVAL;
		return addr;
	}

	if (addr) {
		addr = ALIGN(addr, huge_page_size(h));
		vma = find_vma(mm, addr);
		if (mm->task_size - len >= addr &&
		    (!vma || addr + len <= vma->vm_start))
			return addr;
	}
	
	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = current->mm->mmap_base;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;

	if (addr > DEFAULT_MAP_WINDOW)
		info.high_limit += mm->context.addr_limit - DEFAULT_MAP_WINDOW;

	return vm_unmapped_area(&info);
}