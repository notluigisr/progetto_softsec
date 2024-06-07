static inline struct htx_blk *htx_add_trailer(struct htx *htx, const struct ist name,
					      const struct ist value)
{
	struct htx_blk *blk;

	
	blk = htx_add_blk(htx, HTX_BLK_TLR, name.len + value.len);
	if (!blk)
		return NULL;

	blk->info += (value.len << 8) + name.len;
	ist2bin_lc(htx_get_blk_ptr(htx, blk), name);
	memcpy(htx_get_blk_ptr(htx, blk)  + name.len, value.ptr, value.len);
	return blk;
}