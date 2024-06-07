ext4_xattr_check_entries(struct ext4_xattr_entry *entry, void *end,
			 void *value_start)
{
	struct ext4_xattr_entry *e = entry;

	
	while (!IS_LAST_ENTRY(e)) {
		struct ext4_xattr_entry *next = EXT4_XATTR_NEXT(e);
		if ((void *)next >= end)
			return -EFSCORRUPTED;
		e = next;
	}

	
	while (!IS_LAST_ENTRY(entry)) {
		u32 size = le32_to_cpu(entry->e_value_size);

		if (size > INT_MAX)
			return -EFSCORRUPTED;

		if (size != 0 && entry->e_value_inum == 0) {
			u16 offs = le16_to_cpu(entry->e_value_offs);
			void *value;

			
			if (offs > end - value_start)
				return -EFSCORRUPTED;
			value = value_start + offs;
			if (value < (void *)e + sizeof(u32) ||
			    size > end - value ||
			    EXT4_XATTR_SIZE(size) > end - value)
				return -EFSCORRUPTED;
		}
		entry = EXT4_XATTR_NEXT(entry);
	}

	return 0;
}