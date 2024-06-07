get_uncompressed_data(struct archive_read *a, const void **buff, size_t size,
    size_t minimum)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	ssize_t bytes_avail;

	if (zip->codec == _7Z_COPY && zip->codec2 == (unsigned long)-1) {
		

		
		*buff = __archive_read_ahead(a, 1, &bytes_avail);
		if (bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "STR");
			return (ARCHIVE_FATAL);
		}
		if ((size_t)bytes_avail >
		    zip->uncompressed_buffer_bytes_remaining)
			bytes_avail = (ssize_t)
			    zip->uncompressed_buffer_bytes_remaining;
		if ((size_t)bytes_avail > size)
			bytes_avail = (ssize_t)size;

		zip->pack_stream_bytes_unconsumed = bytes_avail;
	} else if (zip->uncompressed_buffer_pointer == NULL) {
		
		archive_set_error(&(a->archive),
		    ARCHIVE_ERRNO_MISC, "STR");
		return (ARCHIVE_FATAL);
	} else {
		
		if (minimum > zip->uncompressed_buffer_bytes_remaining) {
			
			if (extract_pack_stream(a, minimum) < 0)
				return (ARCHIVE_FATAL);
		}
		if (size > zip->uncompressed_buffer_bytes_remaining)
			bytes_avail = (ssize_t)
			    zip->uncompressed_buffer_bytes_remaining;
		else
			bytes_avail = (ssize_t)size;
		*buff = zip->uncompressed_buffer_pointer;
		zip->uncompressed_buffer_pointer += bytes_avail;
	}
	zip->uncompressed_buffer_bytes_remaining -= bytes_avail;
	return (bytes_avail);
}