void ext3_update_dynamic_rev(struct super_block *sb)
{
	struct ext3_super_block *es = EXT3_SB(sb)->s_es;

	if (le32_to_cpu(es->s_rev_level) > EXT3_GOOD_OLD_REV)
		return;

	ext3_msg(sb, KERN_WARNING,
		"STR"
		"STR",
		EXT3_DYNAMIC_REV);

	es->s_first_ino = cpu_to_le32(EXT3_GOOD_OLD_FIRST_INO);
	es->s_inode_size = cpu_to_le16(EXT3_GOOD_OLD_INODE_SIZE);
	es->s_rev_level = cpu_to_le32(EXT3_DYNAMIC_REV);
	
	

	
}