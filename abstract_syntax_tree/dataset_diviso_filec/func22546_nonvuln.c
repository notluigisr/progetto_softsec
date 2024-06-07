 */
static bool hva_to_pfn_fast(unsigned long addr, bool write_fault,
			    bool *writable, kvm_pfn_t *pfn)
{
	struct page *page[1];

	
	if (!(write_fault || writable))
		return false;

	if (get_user_page_fast_only(addr, FOLL_WRITE, page)) {
		*pfn = page_to_pfn(page[0]);

		if (writable)
			*writable = true;
		return true;
	}

	return false;