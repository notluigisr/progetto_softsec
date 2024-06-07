file_tryelf(struct magic_set *ms, int fd, const unsigned char *buf,
    size_t nbytes)
{
	union {
		int32_t l;
		char c[sizeof (int32_t)];
	} u;
	int clazz;
	int swap;
	struct stat st;
	off_t fsize;
	int flags = 0;
	Elf32_Ehdr elf32hdr;
	Elf64_Ehdr elf64hdr;
	uint16_t type;

	if (ms->flags & (MAGIC_MIME|MAGIC_APPLE))
		return 0;
	
	if (buf[EI_MAG0] != ELFMAG0
	    || (buf[EI_MAG1] != ELFMAG1 && buf[EI_MAG1] != OLFMAG1)
	    || buf[EI_MAG2] != ELFMAG2 || buf[EI_MAG3] != ELFMAG3)
		return 0;

	
	if((lseek(fd, (off_t)0, SEEK_SET) == (off_t)-1) && (errno == ESPIPE))
		fd = file_pipe2file(ms, fd, buf, nbytes);

	if (fstat(fd, &st) == -1) {
  		file_badread(ms);
		return -1;
	}
	fsize = st.st_size;

	clazz = buf[EI_CLASS];

	switch (clazz) {
	case ELFCLASS32:
#undef elf_getu

#undef elfhdr


	case ELFCLASS64:
#undef elf_getu

#undef elfhdr


	default:
	    if (file_printf(ms, "STR", clazz) == -1)
		    return -1;
	    break;
	}
	return 0;
}