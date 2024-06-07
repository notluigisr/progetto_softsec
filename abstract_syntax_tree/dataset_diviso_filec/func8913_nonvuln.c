static int _hostfs_fdatasync(oe_fd_t* desc)
{
    int ret = -1;
    file_t* file = _cast_file(desc);

    if (!file)
        OE_RAISE_ERRNO(OE_EINVAL);

    if (oe_syscall_fdatasync_ocall(&ret, file->host_fd) != OE_OK)
        OE_RAISE_ERRNO(OE_EINVAL);

done:
    return ret;
}