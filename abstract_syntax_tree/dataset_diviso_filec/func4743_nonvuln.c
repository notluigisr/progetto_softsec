static void get_strings_range(RBinFile *arch, RList *list, int min, ut64 from, ut64 to) {
	RBinPlugin *plugin = r_bin_file_cur_plugin (arch);
	RBinString *ptr;
	RListIter *it;

	if (!arch || !arch->buf || !arch->buf->buf) {
		return;
	}
	if (!arch->rawstr) {
		if (!plugin || !plugin->info) {
			return;
		}
	}
	if (!min) {
		min = plugin? plugin->minstrlen: 4;
	}
	
	if (!min) {
		min = 4;
	}
	if (min < 0) {
		return;
	}
	if (!to || to > arch->buf->length) {
		to = arch->buf->length;
	}
	if (arch->rawstr != 2) {
		ut64 size = to - from;
		
		if (arch->rbin->maxstrbuf && size && size > arch->rbin->maxstrbuf) {
			if (arch->rbin->verbose) {
				eprintf ("STR"
					"STR" PFMT64x
					"STR"
					"STR"
					"STR",
					size);
			}
			return;
		}
	}
	if (string_scan_range (list, arch->buf->buf, min, from, to, -1) < 0) {
		return;
	}
	r_list_foreach (list, it, ptr) {
		RBinSection *s = r_bin_get_section_at (arch->o, ptr->paddr, false);
		if (s) {
			ptr->vaddr = s->vaddr + (ptr->paddr - s->paddr);
		}
	}
}