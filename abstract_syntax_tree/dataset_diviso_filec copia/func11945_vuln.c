static int aspeed_lpc_ctrl_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct aspeed_lpc_ctrl *lpc_ctrl = file_aspeed_lpc_ctrl(file);
	unsigned long vsize = vma->vm_end - vma->vm_start;
	pgprot_t prot = vma->vm_page_prot;

	if (vma->vm_pgoff + vsize > lpc_ctrl->mem_base + lpc_ctrl->mem_size)
		return -EINVAL;

	
	prot = pgprot_noncached(prot);

	if (remap_pfn_range(vma, vma->vm_start,
		(lpc_ctrl->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, prot))
		return -EAGAIN;

	return 0;
}