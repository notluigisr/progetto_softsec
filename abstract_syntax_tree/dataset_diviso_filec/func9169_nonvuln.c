static oe_off_t _consolefs_lseek(oe_fd_t* file_, oe_off_t offset, int whence)
{
    oe_off_t ret = -1;

    OE_UNUSED(file_);
    OE_UNUSED(offset);
    OE_UNUSED(whence);
    OE_RAISE_ERRNO(OE_ESPIPE);

done:
    return ret;
}