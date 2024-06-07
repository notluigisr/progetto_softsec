print_just_file_entry_details(Dwarf_Debug dbg,
    Dwarf_Line_Context line_context)
{
    unsigned fiu = 0;
    Dwarf_File_Entry fe = line_context->lc_file_entries;
    Dwarf_File_Entry fe2 = fe;
    dwarfstring m3;

    dwarfstring_constructor_static(&m3,locallinebuf,
        sizeof(locallinebuf));
    dwarfstring_append_printf_i(&m3,
        "STR",
        line_context->lc_file_entry_count);
    _dwarf_printf(dbg,dwarfstring_string(&m3));
    dwarfstring_reset(&m3);
    for (fiu = 0 ; fe2 ; fe2 = fe->fi_next,++fiu ) {
        Dwarf_Unsigned tlm2 = 0;
        unsigned filenum = 0;

        fe = fe2;
        tlm2 = fe->fi_time_last_mod;
        filenum = fiu+1;

        
        if (line_context->lc_file_entry_count > 9) {
            dwarfstring_append_printf_u(&m3,
                "STR",fiu);
            dwarfstring_append_printf_s(&m3,
                "STR",
                (char *) fe->fi_file_name);
            dwarfstring_append_printf_u(&m3,
                "STR",
                filenum);
        } else {
            dwarfstring_append_printf_u(&m3,
                "STR", fiu);
            dwarfstring_append_printf_s(&m3,
                "STR",(char *)fe->fi_file_name);
            dwarfstring_append_printf_u(&m3,
                "STR",filenum);
        }
        _dwarf_printf(dbg,dwarfstring_string(&m3));
        dwarfstring_reset(&m3);
        if (fe->fi_dir_index_present) {
            Dwarf_Unsigned di = 0;
            di = fe->fi_dir_index;
            dwarfstring_append_printf_i(&m3,
                "STR", di);
        }
        if (fe->fi_time_last_mod_present) {
            time_t tt = (time_t) tlm2;

            
            dwarfstring_append_printf_u(&m3,
                "STR",tlm2);
            dwarfstring_append(&m3,(char *)ctime(&tt));
        }
        if (fe->fi_file_length_present) {
            Dwarf_Unsigned fl = 0;

            fl = fe->fi_file_length;
            dwarfstring_append_printf_i(&m3,
                "STR",fl);
            dwarfstring_append_printf_u(&m3,
                "STR",fl);
        }
        if (fe->fi_md5_present) {
            char *c = (char *)&fe->fi_md5_value;
            char *end = c+sizeof(fe->fi_md5_value);
            dwarfstring_append(&m3, "STR");
            while(c < end) {
                dwarfstring_append_printf_u(&m3,
                    "STR",0xff&*c);
                ++c;
            }
            dwarfstring_append(&m3,"STR");
        }
        if (dwarfstring_strlen(&m3)) {
            _dwarf_printf(dbg,dwarfstring_string(&m3));
            dwarfstring_reset(&m3);
        }
    }
    dwarfstring_destructor(&m3);
}