static ssize_t _consolefs_writev(
    oe_fd_t* desc,
    const struct oe_iovec* iov,
    int iovcnt)
{
    ssize_t ret = -1;
    file_t* file = _cast_file(desc);
    void* buf = NULL;
    size_t buf_size = 0;
    size_t data_size = 0;

    if (!file || (!iov && iovcnt) || iovcnt < 0 || iovcnt > OE_IOV_MAX)
        OE_RAISE_ERRNO(OE_EINVAL);

    
    if (oe_iov_pack(iov, iovcnt, &buf, &buf_size, &data_size) != 0)
        OE_RAISE_ERRNO(OE_ENOMEM);

    
    if (data_size > OE_SSIZE_MAX)
        OE_RAISE_ERRNO(OE_EINVAL);

    
    if (oe_syscall_writev_ocall(&ret, file->host_fd, buf, iovcnt, buf_size) !=
        OE_OK)
    {
        OE_RAISE_ERRNO(OE_EINVAL);
    }

    
    if (ret > (ssize_t)data_size)
    {
        ret = -1;
        OE_RAISE_ERRNO(OE_EINVAL);
    }

done:

    if (buf)
        oe_free(buf);

    return ret;
}