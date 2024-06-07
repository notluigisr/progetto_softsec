static void allwinner_ahci_init(Object *obj)
{
    SysbusAHCIState *s = SYSBUS_AHCI(obj);
    AllwinnerAHCIState *a = ALLWINNER_AHCI(obj);

    memory_region_init_io(&a->mmio, OBJECT(obj), &allwinner_ahci_mem_ops, a,
                          "STR", ALLWINNER_AHCI_MMIO_SIZE);
    memory_region_add_subregion(&s->ahci.mem, ALLWINNER_AHCI_MMIO_OFF,
                                &a->mmio);
}