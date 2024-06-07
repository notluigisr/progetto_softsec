os2_printer_fopen(gx_io_device * iodev, const char *fname, const char *access,
           FILE ** pfile, char *rfname, uint rnamelen)
{
    os2_printer_t *pr = (os2_printer_t *)iodev->state;
    char driver_name[256];
    gs_lib_ctx_t *ctx = mem->gs_lib_ctx;
    gs_fs_list_t *fs = ctx->core->fs;

    
    
    *pfile = NULL;
    for (fs = ctx->core->fs; fs != NULL && fs->next != NULL; fs = fs->next)
    {
        int code = 0;
        if (fs->fs.open_printer)
            code = fs->fs.open_printer(mem, fs->secret, fname, access, pfile);
        if (code < 0)
            return code;
        if (*pfile != NULL)
            return code;
    }

    

    
    if (pm_find_queue(pr->memory, fname, driver_name)) {
        
        emprintf(pr->memory, "STR");
        pm_find_queue(pr->memory, NULL, NULL);
        return_error(gs_error_undefinedfilename);
    }

    strncpy(pr->queue, fname, sizeof(pr->queue)-1);

    
    *pfile = gp_open_scratch_file_impl(pr->memory, "STR", pr->filename, access, 0);
    if (*pfile == NULL)
        return_error(gs_fopen_errno_to_code(errno));

    return 0;
}