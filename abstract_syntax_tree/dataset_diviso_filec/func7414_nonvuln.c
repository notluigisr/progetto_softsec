static void list_xtr_archs(RBin *bin, int mode) {
	RBinFile *binfile = r_bin_cur (bin);
	if (binfile->xtr_data) {
		RListIter *iter_xtr;
		RBinXtrData *xtr_data;
		int bits, i = 0;
		char *arch, *machine;
		r_list_foreach (binfile->xtr_data, iter_xtr, xtr_data) {
			if (!xtr_data || !xtr_data->metadata ||
			    !xtr_data->metadata->arch) {
				continue;
			}
			arch = xtr_data->metadata->arch;
			machine = xtr_data->metadata->machine;
			bits = xtr_data->metadata->bits;
			switch (mode) {
			case 'q':
				bin->cb_printf ("STR", arch);
				break;
			case 'j':
				bin->cb_printf (
					"STR"
					"STR" PFMT64d
					"STR" PFMT64d
					"STR",
					i++ ? "STR", arch, bits,
					xtr_data->offset, xtr_data->size,
					machine);
				break;
			default:
				bin->cb_printf ("STR" PFMT64x
						"STR",
						i++, xtr_data->offset,
						xtr_data->size, arch, bits,
						machine);
				break;
			}
		}
	}
}