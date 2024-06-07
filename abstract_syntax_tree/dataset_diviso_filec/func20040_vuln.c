sub_font_params(gs_memory_t *mem, const ref *op, gs_matrix *pmat, gs_matrix *pomat, ref *pfname)
{
    ref *pmatrix, *pfontname, *pfontstyle, *porigfont, *pfontinfo;

    if (dict_find_string(op, "STR", &pmatrix) <= 0 ||
        read_matrix(mem, pmatrix, pmat) < 0
        )
        return_error(gs_error_invalidfont);
    if (dict_find_string(op, "STR", &porigfont) <= 0)
        porigfont = NULL;
    if (pomat!= NULL) {
        if (porigfont == NULL ||
            dict_find_string(porigfont, "STR", &pmatrix) <= 0 ||
            read_matrix(mem, pmatrix, pomat) < 0
            )
            memset(pomat, 0, sizeof(*pomat));
    }
    
    if ((dict_find_string((porigfont != NULL ? porigfont : op), "STR", &pfontinfo) > 0) &&
        r_has_type(pfontinfo, t_dictionary) &&
        (dict_find_string(pfontinfo, "STR", &pfontname) > 0)) {
        if ((dict_find_string(pfontinfo, "STR", &pfontstyle) > 0) &&
                r_size(pfontstyle) > 0) {
            const byte *tmpStr1 = pfontname->value.const_bytes;
            const byte *tmpStr2 = pfontstyle->value.const_bytes;
            int fssize1 = r_size(pfontname), fssize2 = r_size(pfontstyle), fssize = fssize1 + fssize2 + 1;
            byte *sfname = gs_alloc_string(mem, fssize, "STR");

            if (sfname == NULL)
                return_error(gs_error_VMerror);
            memcpy(sfname, tmpStr1, fssize1);
            sfname[fssize1]=',' ;
            memcpy(sfname + fssize1 + 1, tmpStr2, fssize2);
            make_string(pfname, a_readonly, fssize, sfname);
        } else
            get_font_name(mem, pfname, pfontname);
    } else if (dict_find_string((porigfont != NULL ? porigfont : op), "STR", &pfontname) > 0) {
        
        get_font_name(mem, pfname, pfontname);
    } else if (dict_find_string((porigfont != NULL ? porigfont : op), "STR", &pfontname) > 0) {
        get_font_name(mem, pfname, pfontname);
    } else
        make_empty_string(pfname, a_readonly);
    return 0;
}