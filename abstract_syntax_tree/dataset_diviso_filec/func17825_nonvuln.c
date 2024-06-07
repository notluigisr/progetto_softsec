long big_key_read(const struct key *key, char __user *buffer, size_t buflen)
{
	size_t datalen = (size_t)key->payload.data[big_key_len];
	long ret;

	if (!buffer || buflen < datalen)
		return datalen;

	if (datalen > BIG_KEY_FILE_THRESHOLD) {
		struct path *path = (struct path *)&key->payload.data[big_key_path];
		struct file *file;
		u8 *data;
		u8 *enckey = (u8 *)key->payload.data[big_key_data];
		size_t enclen = ALIGN(datalen, crypto_skcipher_blocksize(big_key_skcipher));

		data = kmalloc(enclen, GFP_KERNEL);
		if (!data)
			return -ENOMEM;

		file = dentry_open(path, O_RDONLY, current_cred());
		if (IS_ERR(file)) {
			ret = PTR_ERR(file);
			goto error;
		}

		
		ret = kernel_read(file, 0, data, enclen);
		if (ret >= 0 && ret != enclen) {
			ret = -EIO;
			goto err_fput;
		}

		ret = big_key_crypt(BIG_KEY_DEC, data, enclen, enckey);
		if (ret)
			goto err_fput;

		ret = datalen;

		
		if (copy_to_user(buffer, data, datalen) != 0)
			ret = -EFAULT;

err_fput:
		fput(file);
error:
		kfree(data);
	} else {
		ret = datalen;
		if (copy_to_user(buffer, key->payload.data[big_key_data],
				 datalen) != 0)
			ret = -EFAULT;
	}

	return ret;
}