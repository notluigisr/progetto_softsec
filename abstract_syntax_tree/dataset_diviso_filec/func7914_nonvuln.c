static int _hostfs_access(oe_device_t* device, const char* pathname, int mode)
{
    int ret = -1;
    device_t* fs = _cast_device(device);
    char host_path[OE_PATH_MAX];
    const uint32_t MASK = (OE_R_OK | OE_W_OK | OE_X_OK);
    int retval = -1;

    if (!fs || !pathname || ((uint32_t)mode & ~MASK))
        OE_RAISE_ERRNO(OE_EINVAL);

    if (_make_host_path(fs, pathname, host_path) != 0)
        OE_RAISE_ERRNO(oe_errno);

    if (oe_syscall_access_ocall(&retval, host_path, mode) != OE_OK)
        OE_RAISE_ERRNO(OE_EINVAL);

    ret = retval;

done:

    return ret;
}