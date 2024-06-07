static inline void cpu_physical_memory_write_rom_internal(AddressSpace *as,
    hwaddr addr, const uint8_t *buf, int len, enum write_rom_type type)
{
    hwaddr l;
    uint8_t *ptr;
    hwaddr addr1;
    MemoryRegion *mr;

    while (len > 0) {
        l = len;
        mr = address_space_translate(as, addr, &addr1, &l, true);

        if (!(memory_region_is_ram(mr) ||
              memory_region_is_romd(mr))) {
            
        } else {
            addr1 += memory_region_get_ram_addr(mr);
            
            ptr = qemu_get_ram_ptr(addr1);
            switch (type) {
            case WRITE_DATA:
                memcpy(ptr, buf, l);
                invalidate_and_set_dirty(addr1, l);
                break;
            case FLUSH_CACHE:
                flush_icache_range((uintptr_t)ptr, (uintptr_t)ptr + l);
                break;
            }
        }
        len -= l;
        buf += l;
        addr += l;
    }
}