static struct page *syscall_nopage(struct vm_area_struct *vma,
				unsigned long adr, int *type)
{
	struct page *p = virt_to_page(adr - vma->vm_start + syscall_page);
	get_page(p);
	return p;
}