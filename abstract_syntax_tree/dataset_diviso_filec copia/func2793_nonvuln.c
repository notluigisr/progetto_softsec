errcode_t ext2fs_close_free(ext2_filsys *fs_ptr)
{
	errcode_t ret;
	ext2_filsys fs = *fs_ptr;

	ret = ext2fs_close2(fs, 0);
	if (ret)
		ext2fs_free(fs);
	*fs_ptr = NULL;
	return ret;
}