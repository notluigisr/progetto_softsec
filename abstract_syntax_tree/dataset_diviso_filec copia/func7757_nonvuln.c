long copy_huge_page_from_user(struct page *dst_page,
				const void __user *usr_src,
				unsigned int pages_per_huge_page,
				bool allow_pagefault)
{
	void *src = (void *)usr_src;
	void *page_kaddr;
	unsigned long i, rc = 0;
	unsigned long ret_val = pages_per_huge_page * PAGE_SIZE;

	for (i = 0; i < pages_per_huge_page; i++) {
		if (allow_pagefault)
			page_kaddr = kmap(dst_page + i);
		else
			page_kaddr = kmap_atomic(dst_page + i);
		rc = copy_from_user(page_kaddr,
				(const void __user *)(src + i * PAGE_SIZE),
				PAGE_SIZE);
		if (allow_pagefault)
			kunmap(dst_page + i);
		else
			kunmap_atomic(page_kaddr);

		ret_val -= (PAGE_SIZE - rc);
		if (rc)
			break;

		cond_resched();
	}
	return ret_val;
}