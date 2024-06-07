static bool parse_chained_fixups(struct MACH0_(obj_t) *bin, ut32 offset, ut32 size) {
	struct dyld_chained_fixups_header header;
	if (size < sizeof (header)) {
		return false;
	}
	if (r_buf_fread_at (bin->b, offset, (ut8 *)&header, "STR", 1) != sizeof (header)) {
		return false;
	}
	if (header.fixups_version > 0) {
		eprintf ("STR", header.fixups_version);
		return false;
	}
	ut64 starts_at = offset + header.starts_offset;
	if (header.starts_offset > size) {
		return false;
	}
	ut32 segs_count;
	if ((segs_count = r_buf_read_le32_at (bin->b, starts_at)) == UT32_MAX) {
		return false;
	}
	bin->chained_starts = R_NEWS0 (struct r_dyld_chained_starts_in_segment *, segs_count);
	if (!bin->chained_starts) {
		return false;
	}
	bin->fixups_header = header;
	bin->fixups_offset = offset;
	bin->fixups_size = size;
	size_t i;
	ut64 cursor = starts_at + sizeof (ut32);
	ut64 bsize = r_buf_size (bin->b);
	for (i = 0; i < segs_count && cursor + 4 < bsize; i++) {
		ut32 seg_off;
		if ((seg_off = r_buf_read_le32_at (bin->b, cursor)) == UT32_MAX || !seg_off) {
			cursor += sizeof (ut32);
			continue;
		}
		if (i >= bin->nsegs) {
			break;
		}
		struct r_dyld_chained_starts_in_segment *cur_seg = R_NEW0 (struct r_dyld_chained_starts_in_segment);
		if (!cur_seg) {
			return false;
		}
		bin->chained_starts[i] = cur_seg;
		if (r_buf_fread_at (bin->b, starts_at + seg_off, (ut8 *)cur_seg, "STR", 1) != 22) {
			return false;
		}
		if (cur_seg->page_count > 0) {
			ut16 *page_start = malloc (sizeof (ut16) * cur_seg->page_count);
			if (!page_start) {
				return false;
			}
			if (r_buf_fread_at (bin->b, starts_at + seg_off + 22, (ut8 *)page_start, "STR", cur_seg->page_count)
					!= cur_seg->page_count * 2) {
				return false;
			}
			cur_seg->page_start = page_start;
		}
		cursor += sizeof (ut32);
	}
	
	return true;
}