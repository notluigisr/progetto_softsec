static uint32_t sm501_palette_read(void *opaque, hwaddr addr)
{
    SM501State *s = (SM501State *)opaque;
    SM501_DPRINTF("STR", (int)addr);

    
    

    assert(range_covers_byte(0, 0x400 * 3, addr));
    return *(uint32_t *)&s->dc_palette[addr];
}