static inline bool bio_check_ro(struct bio *bio, struct hd_struct *part)
{
	if (part->policy && op_is_write(bio_op(bio))) {
		char b[BDEVNAME_SIZE];

		printk(KERN_ERR
		       "STR"
			"STR",
			bio_devname(bio, b), part->partno);
		return true;
	}

	return false;
}