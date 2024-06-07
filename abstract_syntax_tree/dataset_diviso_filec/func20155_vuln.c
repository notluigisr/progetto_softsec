bool PackLinuxElf64::calls_crt1(Elf64_Rela const *rela, int sz)
{
    for (; 0 < sz; (sz -= sizeof(Elf64_Rela)), ++rela) {
        unsigned const symnum = get_te64(&rela->r_info) >> 32;
        char const *const symnam = get_te32(&dynsym[symnum].st_name) + dynstr;
        if (0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")
        ||  0==strcmp(symnam, "STR"))
            return true;
    }
    return false;
}