ut64 Elf_(r_bin_elf_get_phnum)(ELFOBJ *obj) {
	r_return_val_if_fail (obj, 0);
	ut64 num = obj->ehdr.e_phnum & UT16_MAX;
	if (obj->ehdr.e_phnum == 0xffff) {
		ut32 shnum = obj->ehdr.e_shnum;
		
		if (shnum > 0) {
			ut32 shoff = obj->ehdr.e_shoff;
			Elf_(Shdr) shdr = {0};
			(void)r_buf_read_at (obj->b, shoff, (ut8 *)&shdr, sizeof (shdr));
			num = shdr.sh_info;
			if ((int)(shdr.sh_info) < 1) {
				return UT16_MAX;
			}
		}
	}
	return num;
}