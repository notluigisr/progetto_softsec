int read_record_hdr(int ifd, void *buffer, struct record_header *record_hdr,
		    struct file_header *file_hdr, int arch_64, int endian_mismatch,
		    int oneof)
{
	int rc;

	if ((rc = sa_fread(ifd, buffer, (size_t) file_hdr->rec_size, SOFT_SIZE, oneof)) != 0)
		
		return rc;

	
	remap_struct(rec_types_nr, file_hdr->rec_types_nr, buffer,
		     file_hdr->rec_size, RECORD_HEADER_SIZE);
	memcpy(record_hdr, buffer, RECORD_HEADER_SIZE);

	
	if (endian_mismatch) {
		swap_struct(rec_types_nr, record_hdr, arch_64);
	}

	return 0;
}