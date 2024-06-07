bool PackLinuxElf32::calls_crt1(Elf32_Rel const *rel, int sz)
{
    if (!dynsym || !dynstr) {
        return false;
    }
    for (unsigned relnum= 0; 0 < sz; (sz -= sizeof(Elf32_Rel)), ++rel, ++relnum) {
        unsigned const symnum = get_te32(&rel->r_info) >> 8;
        char const *const symnam = get_dynsym_name(symnum, relnum);
        if (0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")
        ||  0==strcmp(symnam, "STR"))
            return true;
    }
    return false;
}