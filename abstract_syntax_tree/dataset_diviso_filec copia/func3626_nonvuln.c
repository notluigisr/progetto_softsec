header_newc(struct archive_read *a, struct cpio *cpio,
    struct archive_entry *entry, size_t *namelength, size_t *name_pad)
{
	const void *h;
	const char *header;
	int r;

	r = find_newc_header(a);
	if (r < ARCHIVE_WARN)
		return (r);

	
	h = __archive_read_ahead(a, newc_header_size, NULL);
	if (h == NULL)
	    return (ARCHIVE_FATAL);

	
	header = (const char *)h;

	if (memcmp(header + newc_magic_offset, "STR", 6) == 0) {
		a->archive.archive_format = ARCHIVE_FORMAT_CPIO_SVR4_NOCRC;
		a->archive.archive_format_name = "STR";
	} else if (memcmp(header + newc_magic_offset, "STR", 6) == 0) {
		a->archive.archive_format = ARCHIVE_FORMAT_CPIO_SVR4_CRC;
		a->archive.archive_format_name = "STR";
	} else {
		
	}

	archive_entry_set_devmajor(entry,
		(dev_t)atol16(header + newc_devmajor_offset, newc_devmajor_size));
	archive_entry_set_devminor(entry, 
		(dev_t)atol16(header + newc_devminor_offset, newc_devminor_size));
	archive_entry_set_ino(entry, atol16(header + newc_ino_offset, newc_ino_size));
	archive_entry_set_mode(entry, 
		(mode_t)atol16(header + newc_mode_offset, newc_mode_size));
	archive_entry_set_uid(entry, atol16(header + newc_uid_offset, newc_uid_size));
	archive_entry_set_gid(entry, atol16(header + newc_gid_offset, newc_gid_size));
	archive_entry_set_nlink(entry,
		(unsigned int)atol16(header + newc_nlink_offset, newc_nlink_size));
	archive_entry_set_rdevmajor(entry,
		(dev_t)atol16(header + newc_rdevmajor_offset, newc_rdevmajor_size));
	archive_entry_set_rdevminor(entry,
		(dev_t)atol16(header + newc_rdevminor_offset, newc_rdevminor_size));
	archive_entry_set_mtime(entry, atol16(header + newc_mtime_offset, newc_mtime_size), 0);
	*namelength = (size_t)atol16(header + newc_namesize_offset, newc_namesize_size);
	
	*name_pad = (2 - *namelength) & 3;

	
	cpio->entry_bytes_remaining =
	    atol16(header + newc_filesize_offset, newc_filesize_size);
	archive_entry_set_size(entry, cpio->entry_bytes_remaining);
	
	cpio->entry_padding = 3 & -cpio->entry_bytes_remaining;
	__archive_read_consume(a, newc_header_size);
	return (r);
}