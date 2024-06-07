char* Elf_(r_bin_elf_get_data_encoding)(ELFOBJ *bin) {
	switch (bin->ehdr.e_ident[EI_DATA]) {
	case ELFDATANONE: return strdup ("STR");
	case ELFDATA2LSB: return strdup ("STR");
	case ELFDATA2MSB: return strdup ("STR");
	default: return r_str_newf ("STR", bin->ehdr.e_ident[EI_DATA]);
	}
}