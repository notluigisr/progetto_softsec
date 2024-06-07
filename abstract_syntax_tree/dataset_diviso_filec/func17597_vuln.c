int tpm_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	struct tpm_chip *chip = NULL, *pos;

	rcu_read_lock();
	list_for_each_entry_rcu(pos, &tpm_chip_list, list) {
		if (pos->vendor.miscdev.minor == minor) {
			chip = pos;
			get_device(chip->dev);
			break;
		}
	}
	rcu_read_unlock();

	if (!chip)
		return -ENODEV;

	if (test_and_set_bit(0, &chip->is_open)) {
		dev_dbg(chip->dev, "STR");
		put_device(chip->dev);
		return -EBUSY;
	}

	chip->data_buffer = kmalloc(TPM_BUFSIZE * sizeof(u8), GFP_KERNEL);
	if (chip->data_buffer == NULL) {
		clear_bit(0, &chip->is_open);
		put_device(chip->dev);
		return -ENOMEM;
	}

	atomic_set(&chip->data_pending, 0);

	file->private_data = chip;
	return 0;
}