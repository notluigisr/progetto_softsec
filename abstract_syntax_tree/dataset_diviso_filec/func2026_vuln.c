bool PackLinuxElf32::calls_crt1(Elf32_Rel const *rel, int sz)
{
    for (; 0 < sz; (sz -= sizeof(Elf32_Rel)), ++rel) {
        unsigned const symnum = get_te32(&rel->r_info) >> 8;
        char const *const symnam = get_te32(&dynsym[symnum].st_name) + dynstr;
        if (0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")  
        ||  0==strcmp(symnam, "STR")
        ||  0==strcmp(symnam, "STR"))
            return true;
    }
    return false;
}