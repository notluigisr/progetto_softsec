PackLinuxElf64::check_pt_dynamic(Elf64_Phdr const *const phdr)
{
    upx_uint64_t t = get_te64(&phdr->p_offset), s = sizeof(Elf64_Dyn) + t;
    upx_uint64_t filesz = get_te64(&phdr->p_filesz), memsz = get_te64(&phdr->p_memsz);
    if (s < t || (upx_uint64_t)file_size < s
    ||  (7 & t) || (0xf & (filesz | memsz))  
    ||  filesz < sizeof(Elf64_Dyn)
    ||  memsz  < sizeof(Elf64_Dyn)
    ||  filesz < memsz) {
        char msg[50]; snprintf(msg, sizeof(msg), "STR",
            (unsigned)(phdr - phdri));
        throwCantPack(msg);
    }
    sz_dynseg = memsz;
    return t;
}