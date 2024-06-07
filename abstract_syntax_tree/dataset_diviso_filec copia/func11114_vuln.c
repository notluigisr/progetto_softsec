dma_cookie_t dma_memcpy_pg_to_iovec(struct dma_chan *chan, struct iovec *iov,
	struct dma_pinned_list *pinned_list, struct page *page,
	unsigned int offset, size_t len)
{
	int iov_byte_offset;
	int copy;
	dma_cookie_t dma_cookie = 0;
	int iovec_idx;
	int page_idx;
	int err;

	
	
	if (!chan || !pinned_list) {
		u8 *vaddr = kmap(page);
		err = memcpy_toiovec(iov, vaddr + offset, len);
		kunmap(page);
		return err;
	}

	iovec_idx = 0;
	while (iovec_idx < pinned_list->nr_iovecs) {
		struct dma_page_list *page_list;

		
		while (!iov[iovec_idx].iov_len)
			iovec_idx++;

		page_list = &pinned_list->page_list[iovec_idx];

		iov_byte_offset = ((unsigned long)iov[iovec_idx].iov_base & ~PAGE_MASK);
		page_idx = (((unsigned long)iov[iovec_idx].iov_base & PAGE_MASK)
			 - ((unsigned long)page_list->base_address & PAGE_MASK)) >> PAGE_SHIFT;

		
		while (iov[iovec_idx].iov_len) {
			copy = min_t(int, PAGE_SIZE - iov_byte_offset, len);
			copy = min_t(int, copy, iov[iovec_idx].iov_len);

			dma_cookie = dma_async_memcpy_pg_to_pg(chan,
					page_list->pages[page_idx],
					iov_byte_offset,
					page,
					offset,
					copy);
			
			if (unlikely(dma_cookie < 0)) {
				dma_async_issue_pending(chan);
				continue;
			}

			len -= copy;
			iov[iovec_idx].iov_len -= copy;
			iov[iovec_idx].iov_base += copy;

			if (!len)
				return dma_cookie;

			offset += copy;
			iov_byte_offset = 0;
			page_idx++;
		}
		iovec_idx++;
	}

	
	BUG();
	return -EFAULT;
}