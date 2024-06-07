ssize_t tpm_write(struct file *file, const char __user *buf,
		  size_t size, loff_t *off)
{
	struct tpm_chip *chip = file->private_data;
	size_t in_size = size, out_size;

	
	while (atomic_read(&chip->data_pending) != 0)
		msleep(TPM_TIMEOUT);

	mutex_lock(&chip->buffer_mutex);

	if (in_size > TPM_BUFSIZE)
		in_size = TPM_BUFSIZE;

	if (copy_from_user
	    (chip->data_buffer, (void __user *) buf, in_size)) {
		mutex_unlock(&chip->buffer_mutex);
		return -EFAULT;
	}

	
	out_size = tpm_transmit(chip, chip->data_buffer, TPM_BUFSIZE);

	atomic_set(&chip->data_pending, out_size);
	mutex_unlock(&chip->buffer_mutex);

	
	mod_timer(&chip->user_read_timer, jiffies + (60 * HZ));

	return in_size;
}