static int qxl_init_primary(PCIDevice *dev)
{
    PCIQXLDevice *qxl = DO_UPCAST(PCIQXLDevice, pci, dev);
    VGACommonState *vga = &qxl->vga;
    ram_addr_t ram_size = msb_mask(qxl->vga.vram_size * 2 - 1);

    qxl->id = 0;

    if (ram_size < 32 * 1024 * 1024) {
        ram_size = 32 * 1024 * 1024;
    }
    vga_common_init(vga, ram_size);
    vga_init(vga);
    register_ioport_write(0x3c0, 16, 1, qxl_vga_ioport_write, vga);
    register_ioport_write(0x3b4,  2, 1, qxl_vga_ioport_write, vga);
    register_ioport_write(0x3d4,  2, 1, qxl_vga_ioport_write, vga);
    register_ioport_write(0x3ba,  1, 1, qxl_vga_ioport_write, vga);
    register_ioport_write(0x3da,  1, 1, qxl_vga_ioport_write, vga);

    vga->ds = graphic_console_init(qxl_hw_update, qxl_hw_invalidate,
                                   qxl_hw_screen_dump, qxl_hw_text_update, qxl);
    qemu_spice_display_init_common(&qxl->ssd, vga->ds);

    qxl0 = qxl;
    register_displaychangelistener(vga->ds, &display_listener);

    return qxl_init_common(qxl);
}