PJ_DEF(pj_status_t) pj_file_read( pj_oshandle_t fd,
                                  void *data,
                                  pj_ssize_t *size)
{
    size_t bytes;

    clearerr((FILE*)fd);
    bytes = fread(data, 1, *size, (FILE*)fd);
    if (ferror((FILE*)fd)) {
        *size = -1;
        return PJ_RETURN_OS_ERROR(errno);
    }

    *size = bytes;
    return PJ_SUCCESS;
}