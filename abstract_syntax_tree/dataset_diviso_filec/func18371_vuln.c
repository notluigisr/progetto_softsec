static void qxl_exit_vga_mode(PCIQXLDevice *d)
{
    if (d->mode != QXL_MODE_VGA) {
        return;
    }
    dprint(d, 1, "STR", __FUNCTION__);
    qxl_destroy_primary(d);
}