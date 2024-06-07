static int ext4_init_block_bitmap(struct super_block *sb,
				   struct buffer_head *bh,
				   ext4_group_t block_group,
				   struct ext4_group_desc *gdp)
{
	unsigned int bit, bit_max;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t start, tmp;

	J_ASSERT_BH(bh, buffer_locked(bh));

	
	if (!ext4_group_desc_csum_verify(sb, block_group, gdp)) {
		ext4_mark_group_bitmap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT |
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		return -EFSBADCRC;
	}
	memset(bh->b_data, 0, sb->s_blocksize);

	bit_max = ext4_num_base_meta_clusters(sb, block_group);
	if ((bit_max >> 3) >= bh->b_size)
		return -EFSCORRUPTED;

	for (bit = 0; bit < bit_max; bit++)
		ext4_set_bit(bit, bh->b_data);

	start = ext4_group_first_block_no(sb, block_group);

	
	tmp = ext4_block_bitmap(sb, gdp);
	if (ext4_block_in_group(sb, tmp, block_group))
		ext4_set_bit(EXT4_B2C(sbi, tmp - start), bh->b_data);

	tmp = ext4_inode_bitmap(sb, gdp);
	if (ext4_block_in_group(sb, tmp, block_group))
		ext4_set_bit(EXT4_B2C(sbi, tmp - start), bh->b_data);

	tmp = ext4_inode_table(sb, gdp);
	for (; tmp < ext4_inode_table(sb, gdp) +
		     sbi->s_itb_per_group; tmp++) {
		if (ext4_block_in_group(sb, tmp, block_group))
			ext4_set_bit(EXT4_B2C(sbi, tmp - start), bh->b_data);
	}

	
	ext4_mark_bitmap_end(num_clusters_in_group(sb, block_group),
			     sb->s_blocksize * 8, bh->b_data);
	return 0;
}