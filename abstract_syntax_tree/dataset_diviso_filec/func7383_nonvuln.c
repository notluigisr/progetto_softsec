int hfsplus_block_free(struct super_block *sb, u32 offset, u32 count)
{
	struct page *page;
	struct address_space *mapping;
	__be32 *pptr, *curr, *end;
	u32 mask, len, pnr;
	int i;

	
	if (!count)
		return 0;

	dprint(DBG_BITMAP, "STR", offset, count);
	
	if ((offset + count) > HFSPLUS_SB(sb).total_blocks)
		return -2;

	mutex_lock(&HFSPLUS_SB(sb).alloc_file->i_mutex);
	mapping = HFSPLUS_SB(sb).alloc_file->i_mapping;
	pnr = offset / PAGE_CACHE_BITS;
	page = read_mapping_page(mapping, pnr, NULL);
	pptr = kmap(page);
	curr = pptr + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	end = pptr + PAGE_CACHE_BITS / 32;
	len = count;

	
	i = offset % 32;
	if (i) {
		int j = 32 - i;
		mask = 0xffffffffU << j;
		if (j > count) {
			mask |= 0xffffffffU >> (i + count);
			*curr++ &= cpu_to_be32(mask);
			goto out;
		}
		*curr++ &= cpu_to_be32(mask);
		count -= j;
	}

	
	while (1) {
		while (curr < end) {
			if (count < 32)
				goto done;
			*curr++ = 0;
			count -= 32;
		}
		if (!count)
			break;
		set_page_dirty(page);
		kunmap(page);
		page = read_mapping_page(mapping, ++pnr, NULL);
		pptr = kmap(page);
		curr = pptr;
		end = pptr + PAGE_CACHE_BITS / 32;
	}
done:
	
	if (count) {
		mask = 0xffffffffU >> count;
		*curr &= cpu_to_be32(mask);
	}
out:
	set_page_dirty(page);
	kunmap(page);
	HFSPLUS_SB(sb).free_blocks += len;
	sb->s_dirt = 1;
	mutex_unlock(&HFSPLUS_SB(sb).alloc_file->i_mutex);

	return 0;
}