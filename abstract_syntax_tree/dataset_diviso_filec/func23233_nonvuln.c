static void mb_cmp_bitmaps(struct ext4_buddy *e4b, void *bitmap)
{
	if (memcmp(e4b->bd_info->bb_bitmap, bitmap, e4b->bd_sb->s_blocksize)) {
		unsigned char *b1, *b2;
		int i;
		b1 = (unsigned char *) e4b->bd_info->bb_bitmap;
		b2 = (unsigned char *) bitmap;
		for (i = 0; i < e4b->bd_sb->s_blocksize; i++) {
			if (b1[i] != b2[i]) {
				ext4_msg(e4b->bd_sb, KERN_ERR,
					 "STR"
					 "STR"
					 "STR",
					 e4b->bd_group, i, i * 8, b1[i], b2[i]);
				BUG();
			}
		}
	}
}