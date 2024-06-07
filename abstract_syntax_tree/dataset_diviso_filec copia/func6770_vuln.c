void __init(RBuffer *buf, r_bin_ne_obj_t *bin) {
	bin->header_offset = r_buf_read_le16_at (buf, 0x3c);
	bin->ne_header = R_NEW0 (NE_image_header);
	if (!bin->ne_header) {
		return;
	}
	bin->buf = buf;
	r_buf_read_at (buf, bin->header_offset, (ut8 *)bin->ne_header, sizeof (NE_image_header));
	bin->alignment = 1 << bin->ne_header->FileAlnSzShftCnt;
	if (!bin->alignment) {
		bin->alignment = 1 << 9;
	}
	bin->os = __get_target_os (bin);

	ut16 offset = bin->ne_header->SegTableOffset + bin->header_offset;
	ut16 size = bin->ne_header->SegCount * sizeof (NE_image_segment_entry);
	bin->segment_entries = calloc (1, size);
	if (!bin->segment_entries) {
		return;
	}
	r_buf_read_at (buf, offset, (ut8 *)bin->segment_entries, size);
	bin->entry_table = calloc (1, bin->ne_header->EntryTableLength);
	r_buf_read_at (buf, (ut64)bin->header_offset + bin->ne_header->EntryTableOffset, bin->entry_table, bin->ne_header->EntryTableLength);
	bin->imports = r_bin_ne_get_imports (bin);
	__ne_get_resources (bin);
}