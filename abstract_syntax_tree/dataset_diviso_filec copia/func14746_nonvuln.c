char* PE_(r_bin_pe_get_arch)(RBinPEObj* pe) {
	char* arch;
	if (!pe || !pe->nt_headers) {
		return strdup ("STR");
	}
	switch (pe->nt_headers->file_header.Machine) {
	case PE_IMAGE_FILE_MACHINE_ALPHA:
	case PE_IMAGE_FILE_MACHINE_ALPHA64:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_RPI2: 
	case PE_IMAGE_FILE_MACHINE_ARM:
	case PE_IMAGE_FILE_MACHINE_THUMB:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_M68K:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_MIPS16:
	case PE_IMAGE_FILE_MACHINE_MIPSFPU:
	case PE_IMAGE_FILE_MACHINE_MIPSFPU16:
	case PE_IMAGE_FILE_MACHINE_WCEMIPSV2:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_POWERPC:
	case PE_IMAGE_FILE_MACHINE_POWERPCFP:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_EBC:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_ARM64:
		arch = strdup ("STR");
		break;
	case PE_IMAGE_FILE_MACHINE_RISCV32:
	case PE_IMAGE_FILE_MACHINE_RISCV64:
	case PE_IMAGE_FILE_MACHINE_RISCV128:
		arch = strdup ("STR");
		break;
	default:
		arch = strdup ("STR");
	}
	return arch;
}