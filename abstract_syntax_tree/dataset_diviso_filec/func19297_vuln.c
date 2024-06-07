static int qxl_init_common(PCIQXLDevice *qxl)
{
    uint8_t* config = qxl->pci.config;
    uint32_t pci_device_rev;
    uint32_t io_size;

    qxl->mode = QXL_MODE_UNDEFINED;
    qxl->generation = 1;
    qxl->num_memslots = NUM_MEMSLOTS;
    qxl->num_surfaces = NUM_SURFACES;
    qemu_mutex_init(&qxl->track_lock);

    switch (qxl->revision) {
    case 1: 
        pci_device_rev = QXL_REVISION_STABLE_V04;
        break;
    case 2: 
    default:
        pci_device_rev = QXL_REVISION_STABLE_V06;
        break;
    }

    pci_set_byte(&config[PCI_REVISION_ID], pci_device_rev);
    pci_set_byte(&config[PCI_INTERRUPT_PIN], 1);

    qxl->rom_size = qxl_rom_size();
    qxl->rom_offset = qemu_ram_alloc(&qxl->pci.qdev, "STR", qxl->rom_size);
    init_qxl_rom(qxl);
    init_qxl_ram(qxl);

    if (qxl->vram_size < 16 * 1024 * 1024) {
        qxl->vram_size = 16 * 1024 * 1024;
    }
    if (qxl->revision == 1) {
        qxl->vram_size = 4096;
    }
    qxl->vram_size = msb_mask(qxl->vram_size * 2 - 1);
    qxl->vram_offset = qemu_ram_alloc(&qxl->pci.qdev, "STR", qxl->vram_size);

    io_size = msb_mask(QXL_IO_RANGE_SIZE * 2 - 1);
    if (qxl->revision == 1) {
        io_size = 8;
    }

    pci_register_bar(&qxl->pci, QXL_IO_RANGE_INDEX,
                     io_size, PCI_BASE_ADDRESS_SPACE_IO, qxl_map);

    pci_register_bar(&qxl->pci, QXL_ROM_RANGE_INDEX,
                     qxl->rom_size, PCI_BASE_ADDRESS_SPACE_MEMORY,
                     qxl_map);

    pci_register_bar(&qxl->pci, QXL_RAM_RANGE_INDEX,
                     qxl->vga.vram_size, PCI_BASE_ADDRESS_SPACE_MEMORY,
                     qxl_map);

    pci_register_bar(&qxl->pci, QXL_VRAM_RANGE_INDEX, qxl->vram_size,
                     PCI_BASE_ADDRESS_SPACE_MEMORY, qxl_map);

    qxl->ssd.qxl.base.sif = &qxl_interface.base;
    qxl->ssd.qxl.id = qxl->id;
    qemu_spice_add_interface(&qxl->ssd.qxl.base);
    qemu_add_vm_change_state_handler(qxl_vm_change_state_handler, qxl);

    init_pipe_signaling(qxl);
    qxl_reset_state(qxl);

    return 0;
}