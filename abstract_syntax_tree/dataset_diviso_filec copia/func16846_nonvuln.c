static int determine_cipher_type(struct fscrypt_info *ci, struct inode *inode,
				 const char **cipher_str_ret, int *keysize_ret)
{
	if (S_ISREG(inode->i_mode)) {
		if (ci->ci_data_mode == FS_ENCRYPTION_MODE_AES_256_XTS) {
			*cipher_str_ret = "STR";
			*keysize_ret = FS_AES_256_XTS_KEY_SIZE;
			return 0;
		}
		pr_warn_once("STR"
			     "STR",
			     ci->ci_data_mode, inode->i_ino);
		return -ENOKEY;
	}

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode)) {
		if (ci->ci_filename_mode == FS_ENCRYPTION_MODE_AES_256_CTS) {
			*cipher_str_ret = "STR";
			*keysize_ret = FS_AES_256_CTS_KEY_SIZE;
			return 0;
		}
		pr_warn_once("STR"
			     "STR",
			     ci->ci_filename_mode, inode->i_ino);
		return -ENOKEY;
	}

	pr_warn_once("STR",
		     (inode->i_mode & S_IFMT), inode->i_ino);
	return -ENOKEY;
}