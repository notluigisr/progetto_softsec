
static inline int bitmap_uptodate(struct buffer_head *bh)
{
	return (buffer_uptodate(bh) &&
			test_bit(BH_BITMAP_UPTODATE, &(bh)->b_state));