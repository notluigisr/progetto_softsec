mswin_handle_fopen(gx_io_device * iodev, const char *fname, const char *access,
                   gp_file ** pfile, char *rfname, uint rnamelen, gs_memory_t *mem)
{
    int fd;
    long hfile;	
    gs_lib_ctx_t *ctx = mem->gs_lib_ctx;
    gs_fs_list_t *fs = ctx->core->fs;

    if (gp_validate_path(mem, fname, access) != 0)
        return gs_error_invalidfileaccess;

    
    
    *pfile = NULL;
    for (fs = ctx->core->fs; fs != NULL && fs->next != NULL; fs = fs->next)
    {
        int code = 0;
        if (fs->fs.open_handle)
            code = fs->fs.open_handle(mem, fs->secret, fname, access, pfile);
        if (code < 0)
            return code;
        if (*pfile != NULL)
            return code;
    }

    
    errno = 0;
    *pfile = gp_file_FILE_alloc(mem);
    if (*pfile == NULL) {
        return gs_error_VMerror;
    }

    if ((hfile = get_os_handle(fname)) == (long)INVALID_HANDLE_VALUE) {
        gp_file_dealloc(*pfile);
        return_error(gs_fopen_errno_to_code(EBADF));
    }

    
    fd = _open_osfhandle((long)hfile, 0);
    if (fd == -1) {
        gp_file_dealloc(*pfile);
        return_error(gs_fopen_errno_to_code(EBADF));
    }

    
    if (gp_file_FILE_set(*pfile, fdopen(fd, (char *)access), NULL)) {
        *pfile = NULL;
        return_error(gs_fopen_errno_to_code(errno));
    }

    if (rfname != NULL)
        strcpy(rfname, fname);

    return 0;
}