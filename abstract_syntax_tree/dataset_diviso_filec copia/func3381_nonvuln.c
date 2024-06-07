tiffscaled_spec_op(gx_device *dev_, int op, void *data, int datasize)
{
    if (op == gxdso_supports_iccpostrender) {
        return true;
    }
    return gdev_prn_dev_spec_op(dev_, op, data, datasize);
}