
static inline  unsigned char get_dtype(struct super_block *sb, int filetype)
{
	if (!ext4_has_feature_filetype(sb) || filetype >= EXT4_FT_MAX)
		return DT_UNKNOWN;

	return ext4_filetype_table[filetype];