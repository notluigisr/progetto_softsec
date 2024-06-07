static void display_refresh(struct DisplayState *ds)
{
    if (qxl0->mode == QXL_MODE_VGA) {
        qemu_spice_display_refresh(&qxl0->ssd);
    }
}