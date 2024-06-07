static void qxl_hw_update(void *opaque)
{
    PCIQXLDevice *qxl = opaque;
    VGACommonState *vga = &qxl->vga;

    switch (qxl->mode) {
    case QXL_MODE_VGA:
        vga->update(vga);
        break;
    case QXL_MODE_COMPAT:
    case QXL_MODE_NATIVE:
        qxl_render_update(qxl);
        break;
    default:
        break;
    }
}