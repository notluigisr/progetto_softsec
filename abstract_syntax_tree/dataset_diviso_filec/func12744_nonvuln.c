static int _hostsock_device_release(oe_device_t* device_)
{
    int ret = -1;
    device_t* device = _cast_device(device_);

    oe_errno = 0;

    if (!device)
        OE_RAISE_ERRNO(OE_EINVAL);

    
    

    ret = 0;

done:

    return ret;
}