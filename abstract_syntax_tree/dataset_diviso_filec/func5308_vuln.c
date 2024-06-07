PackLinuxElf32::PackLinuxElf32help1(InputFile *f)
{
    e_type  = get_te16(&ehdri.e_type);
    e_phnum = get_te16(&ehdri.e_phnum);
    e_shnum = get_te16(&ehdri.e_shnum);
    unsigned const e_phentsize = get_te16(&ehdri.e_phentsize);
    if (ehdri.e_ident[Elf32_Ehdr::EI_CLASS]!=Elf32_Ehdr::ELFCLASS32
    || sizeof(Elf32_Phdr) != e_phentsize
    || (Elf32_Ehdr::ELFDATA2MSB == ehdri.e_ident[Elf32_Ehdr::EI_DATA]
            && &N_BELE_RTP::be_policy != bele)
    || (Elf32_Ehdr::ELFDATA2LSB == ehdri.e_ident[Elf32_Ehdr::EI_DATA]
            && &N_BELE_RTP::le_policy != bele)) {
        e_phoff = 0;
        e_shoff = 0;
        sz_phdrs = 0;
        return;
    }
    e_phoff = get_te32(&ehdri.e_phoff);
    e_shoff = get_te32(&ehdri.e_shoff);
    sz_phdrs = e_phnum * e_phentsize;

    if (f && Elf32_Ehdr::ET_DYN!=e_type) {
        unsigned const len = sz_phdrs + e_phoff;
        alloc_file_image(file_image, len);
        f->seek(0, SEEK_SET);
        f->readx(file_image, len);
        phdri= (Elf32_Phdr       *)(e_phoff + file_image);  
    }
    if (f && Elf32_Ehdr::ET_DYN==e_type) {
        
        alloc_file_image(file_image, file_size);
        f->seek(0, SEEK_SET);
        f->readx(file_image, file_size);
        phdri= (Elf32_Phdr       *)(e_phoff + file_image);  
        shdri= (Elf32_Shdr const *)(e_shoff + file_image);  
        sec_dynsym = elf_find_section_type(Elf32_Shdr::SHT_DYNSYM);
        if (sec_dynsym)
            sec_dynstr = get_te32(&sec_dynsym->sh_link) + shdri;

        Elf32_Phdr const *phdr= phdri;
        for (int j = e_phnum; --j>=0; ++phdr)
        if (Elf32_Phdr::PT_DYNAMIC==get_te32(&phdr->p_type)) {
            dynseg= (Elf32_Dyn const *)(get_te32(&phdr->p_offset) + file_image);
            break;
        }
        
        dynstr =      (char const *)elf_find_dynamic(Elf32_Dyn::DT_STRTAB);
        dynsym = (Elf32_Sym const *)elf_find_dynamic(Elf32_Dyn::DT_SYMTAB);
        gashtab = (unsigned const *)elf_find_dynamic(Elf32_Dyn::DT_GNU_HASH);
        hashtab = (unsigned const *)elf_find_dynamic(Elf32_Dyn::DT_HASH);
        jni_onload_sym = elf_lookup("STR");
        if (jni_onload_sym) {
            jni_onload_va = get_te32(&jni_onload_sym->st_value);
            jni_onload_va = 0;
        }
    }
}