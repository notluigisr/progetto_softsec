gs_add_outputfile_control_path(gs_memory_t *mem, const char *fname)
{
    char *fp, f[gp_file_name_sizeof];
    const int pipe = 124; 
    const int len = strlen(fname);
    int i, code;

    
    if (len >= gp_file_name_sizeof)
        return gs_error_rangecheck;
    strcpy(f, fname);
    fp = f;
    
    rewrite_percent_specifiers(f);
    for (i = 0; i < len; i++) {
        if (f[i] == pipe) {
           fp = &f[i + 1];
           
           code = gs_add_control_path(mem, gs_permit_file_writing, f);
           if (code < 0)
               return code;
           code = gs_add_control_path(mem, gs_permit_file_control, f);
           if (code < 0)
               return code;
           break;
        }
        if (!IS_WHITESPACE(f[i]))
            break;
    }
    code = gs_add_control_path(mem, gs_permit_file_control, fp);
    if (code < 0)
        return code;
    return gs_add_control_path(mem, gs_permit_file_writing, fp);
}