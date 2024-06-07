static void ext4_ext_show_path(struct inode *inode, struct ext4_ext_path *path)
{
	int k, l = path->p_depth;

	ext_debug("STR");
	for (k = 0; k <= l; k++, path++) {
		if (path->p_idx) {
		  ext_debug("STR", le32_to_cpu(path->p_idx->ei_block),
			    idx_pblock(path->p_idx));
		} else if (path->p_ext) {
			ext_debug("STR",
				  le32_to_cpu(path->p_ext->ee_block),
				  ext4_ext_is_uninitialized(path->p_ext),
				  ext4_ext_get_actual_len(path->p_ext),
				  ext_pblock(path->p_ext));
		} else
			ext_debug("STR");
	}
	ext_debug("STR");
}