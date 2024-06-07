static void allwinner_ahci_mem_write(void *opaque, hwaddr addr,
                                     uint64_t val, unsigned size)
{
    AllwinnerAHCIState *a = opaque;

    DPRINTF(-1, "STR",
            addr, val, size);
    a->regs[addr/4] = val;
}