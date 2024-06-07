static int pin_rcv_pages(struct hfi1_filedata *fd, struct tid_user_buf *tidbuf)
{
	int pinned;
	unsigned int npages;
	unsigned long vaddr = tidbuf->vaddr;
	struct page **pages = NULL;
	struct hfi1_devdata *dd = fd->uctxt->dd;

	
	npages = num_user_pages(vaddr, tidbuf->length);
	if (!npages)
		return -EINVAL;

	if (npages > fd->uctxt->expected_count) {
		dd_dev_err(dd, "STR");
		return -EINVAL;
	}

	
	pages = kcalloc(npages, sizeof(*pages), GFP_KERNEL);
	if (!pages)
		return -ENOMEM;

	
	if (!hfi1_can_pin_pages(dd, fd->mm, fd->tid_n_pinned, npages)) {
		kfree(pages);
		return -ENOMEM;
	}

	pinned = hfi1_acquire_user_pages(fd->mm, vaddr, npages, true, pages);
	if (pinned <= 0) {
		kfree(pages);
		return pinned;
	}
	tidbuf->pages = pages;
	tidbuf->npages = npages;
	fd->tid_n_pinned += pinned;
	return pinned;
}