unsigned long arch_get_unmapped_area(struct file *filp, unsigned long addr, unsigned long len,
				     unsigned long pgoff, unsigned long flags)
{
	struct vm_area_struct *vma;
	struct vm_unmapped_area_info info;

	if (len > TASK_SIZE)
		return -ENOMEM;

	
	if (flags & MAP_FIXED)
		return addr;

	
	if (addr) {
		addr = PAGE_ALIGN(addr);
		vma = find_vma(current->mm, addr);
		if (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vma->vm_start))
			goto success;
	}

	
	info.flags = 0;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = (current->mm->start_stack - 0x00200000);
	info.align_mask = 0;
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);
	if (!(addr & ~PAGE_MASK))
		goto success;
	VM_BUG_ON(addr != -ENOMEM);

	
	info.low_limit = PAGE_ALIGN(0x80000000);
	info.high_limit = TASK_SIZE;
	addr = vm_unmapped_area(&info);
	if (!(addr & ~PAGE_MASK))
		goto success;
	VM_BUG_ON(addr != -ENOMEM);

#if 0
	printk("STR",
	       len, filp ? filp->f_path.dentry->d_name.name : "");
#endif
	return -ENOMEM;

 success:
#if 0
	printk("STR",
	       len, addr, filp ? filp->f_path.dentry->d_name.name : "");
#endif
	return addr;
} 