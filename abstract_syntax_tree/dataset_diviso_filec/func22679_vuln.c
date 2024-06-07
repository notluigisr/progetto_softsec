static struct page *get_arg_page(struct linux_binprm *bprm, unsigned long pos,
		int write)
{
	struct page *page;
	int ret;
	unsigned int gup_flags = FOLL_FORCE;

#ifdef CONFIG_STACK_GROWSUP
	if (write) {
		ret = expand_downwards(bprm->vma, pos);
		if (ret < 0)
			return NULL;
	}
#endif

	if (write)
		gup_flags |= FOLL_WRITE;

	
	ret = get_user_pages_remote(current, bprm->mm, pos, 1, gup_flags,
			&page, NULL, NULL);
	if (ret <= 0)
		return NULL;

	if (write) {
		unsigned long size = bprm->vma->vm_end - bprm->vma->vm_start;
		struct rlimit *rlim;

		acct_arg_size(bprm, size / PAGE_SIZE);

		
		if (size <= ARG_MAX)
			return page;

		
		rlim = current->signal->rlim;
		if (size > ACCESS_ONCE(rlim[RLIMIT_STACK].rlim_cur) / 4) {
			put_page(page);
			return NULL;
		}
	}

	return page;
}