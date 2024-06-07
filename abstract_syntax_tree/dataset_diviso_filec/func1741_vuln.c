static int ext4_convert_unwritten_extents_endio(handle_t *handle,
					      struct inode *inode,
					      struct ext4_ext_path *path)
{
	struct ext4_extent *ex;
	int depth;
	int err = 0;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;

	ext_debug("STR"
		"STR", inode->i_ino,
		(unsigned long long)le32_to_cpu(ex->ee_block),
		ext4_ext_get_actual_len(ex));

	err = ext4_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;
	
	ext4_ext_mark_initialized(ex);

	
	ext4_ext_try_to_merge(handle, inode, path, ex);

	
	err = ext4_ext_dirty(handle, inode, path + path->p_depth);
out:
	ext4_ext_show_leaf(inode, path);
	return err;
}