void dump_vma(const struct vm_area_struct *vma)
{
	pr_emerg("STR"
		"STR"
		"STR"
		"STR"
		"STR",
		vma, (void *)vma->vm_start, (void *)vma->vm_end, vma->vm_next,
		vma->vm_prev, vma->vm_mm,
		(unsigned long)pgprot_val(vma->vm_page_prot),
		vma->anon_vma, vma->vm_ops, vma->vm_pgoff,
		vma->vm_file, vma->vm_private_data,
		vma->vm_flags, &vma->vm_flags);
}