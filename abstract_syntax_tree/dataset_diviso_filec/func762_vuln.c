static void mptsas_scsi_realize(PCIDevice *dev, Error **errp)
{
    MPTSASState *s = MPT_SAS(dev);
    Error *err = NULL;
    int ret;

    dev->config[PCI_LATENCY_TIMER] = 0;
    dev->config[PCI_INTERRUPT_PIN] = 0x01;

    if (s->msi != ON_OFF_AUTO_OFF) {
        ret = msi_init(dev, 0, 1, true, false, &err);
        
        assert(!ret || ret == -ENOTSUP);
        if (ret && s->msi == ON_OFF_AUTO_ON) {
            
            error_append_hint(&err, "STR"
                    "STR");
            error_propagate(errp, err);
            return;
        }
        assert(!err || s->msi == ON_OFF_AUTO_AUTO);
        
        error_free(err);

        
        s->msi_in_use = (ret == 0);
    }

    memory_region_init_io(&s->mmio_io, OBJECT(s), &mptsas_mmio_ops, s,
                          "STR", 0x4000);
    memory_region_init_io(&s->port_io, OBJECT(s), &mptsas_port_ops, s,
                          "STR", 256);
    memory_region_init_io(&s->diag_io, OBJECT(s), &mptsas_diag_ops, s,
                          "STR", 0x10000);

    pci_register_bar(dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &s->port_io);
    pci_register_bar(dev, 1, PCI_BASE_ADDRESS_SPACE_MEMORY |
                                 PCI_BASE_ADDRESS_MEM_TYPE_32, &s->mmio_io);
    pci_register_bar(dev, 2, PCI_BASE_ADDRESS_SPACE_MEMORY |
                                 PCI_BASE_ADDRESS_MEM_TYPE_32, &s->diag_io);

    if (!s->sas_addr) {
        s->sas_addr = ((NAA_LOCALLY_ASSIGNED_ID << 24) |
                       IEEE_COMPANY_LOCALLY_ASSIGNED) << 36;
        s->sas_addr |= (pci_dev_bus_num(dev) << 16);
        s->sas_addr |= (PCI_SLOT(dev->devfn) << 8);
        s->sas_addr |= PCI_FUNC(dev->devfn);
    }
    s->max_devices = MPTSAS_NUM_PORTS;

    s->request_bh = qemu_bh_new(mptsas_fetch_requests, s);

    QTAILQ_INIT(&s->pending);

    scsi_bus_new(&s->bus, sizeof(s->bus), &dev->qdev, &mptsas_scsi_info, NULL);
}