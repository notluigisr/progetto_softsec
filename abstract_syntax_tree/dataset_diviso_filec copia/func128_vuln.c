static bool read_phdr(ELFOBJ *bin, bool linux_kernel_hack) {
	bool phdr_found = false;
	int i;
#if R_BIN_ELF64
	const bool is_elf64 = true;
#else
	const bool is_elf64 = false;
#endif
	ut64 phnum = Elf_(r_bin_elf_get_phnum) (bin);
	for (i = 0; i < phnum; i++) {
		ut8 phdr[sizeof (Elf_(Phdr))] = {0};
		int j = 0;
		const size_t rsize = bin->ehdr.e_phoff + i * sizeof (Elf_(Phdr));
		int len = r_buf_read_at (bin->b, rsize, phdr, sizeof (Elf_(Phdr)));
		if (len < 1) {
			R_LOG_ERROR ("STR");
			R_FREE (bin->phdr);
			return false;
		}
		bin->phdr[i].p_type = READ32 (phdr, j);
		if (bin->phdr[i].p_type == PT_PHDR) {
			phdr_found = true;
		}

		if (is_elf64) {
			bin->phdr[i].p_flags = READ32 (phdr, j);
		}
		bin->phdr[i].p_offset = R_BIN_ELF_READWORD (phdr, j);
		bin->phdr[i].p_vaddr = R_BIN_ELF_READWORD (phdr, j);
		bin->phdr[i].p_paddr = R_BIN_ELF_READWORD (phdr, j);
		bin->phdr[i].p_filesz = R_BIN_ELF_READWORD (phdr, j);
		bin->phdr[i].p_memsz = R_BIN_ELF_READWORD (phdr, j);
		if (!is_elf64) {
			bin->phdr[i].p_flags = READ32 (phdr, j);
		
		}
		bin->phdr[i].p_align = R_BIN_ELF_READWORD (phdr, j);
	}
	
	if (linux_kernel_hack && phdr_found) {
		ut64 load_addr = Elf_(r_bin_elf_get_baddr) (bin);
		bin->ehdr.e_phoff = Elf_(r_bin_elf_v2p) (bin, load_addr + bin->ehdr.e_phoff);
		return read_phdr (bin, false);
	}

	return true;
}