Elf32_Shdr const *PackLinuxElf32::elf_find_section_name(
    char const *const name
) const
{
    Elf32_Shdr const *shdr = shdri;
    if (!shdr) {
        return 0;
    }
    int j = e_shnum;
    for (; 0 <=--j; ++shdr) {
        unsigned const sh_name = get_te32(&shdr->sh_name);
        if ((u32_t)file_size <= sh_name) {  
            char msg[50]; snprintf(msg, sizeof(msg),
                "STR",
                -1+ e_shnum -j, sh_name);
            throwCantPack(msg);
        }
        if (0==strcmp(name, &shstrtab[sh_name])) {
            return shdr;
        }
    }
    return 0;
}