int rom_copy(uint8_t *dest, hwaddr addr, size_t size)
{
    hwaddr end = addr + size;
    uint8_t *s, *d = dest;
    size_t l = 0;
    Rom *rom;

    QTAILQ_FOREACH(rom, &roms, next) {
        if (rom->fw_file) {
            continue;
        }
        if (rom->mr) {
            continue;
        }
        if (rom->addr + rom->romsize < addr) {
            continue;
        }
        if (rom->addr > end) {
            break;
        }

        d = dest + (rom->addr - addr);
        s = rom->data;
        l = rom->datasize;

        if ((d + l) > (dest + size)) {
            l = dest - d;
        }

        if (l > 0) {
            memcpy(d, s, l);
        }

        if (rom->romsize > rom->datasize) {
            

            d += l;
            l = rom->romsize - rom->datasize;

            if ((d + l) > (dest + size)) {
                
                l = dest - d;
            }

            if (l > 0) {
                memset(d, 0x0, l);
            }
        }
    }

    return (d + l) - dest;
}