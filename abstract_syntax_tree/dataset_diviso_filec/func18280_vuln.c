     (CirrusVGAState *s, uint32_t dstaddr,
      const uint8_t *src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint32_t colors[2];
    uint32_t addr;
    int x, y;
    unsigned bits;
    unsigned int col;
    unsigned bitmask;
    int srcskipleft = s->vga.gr[0x2f] & 0x07;
    int dstskipleft = srcskipleft * (DEPTH / 8);

    colors[0] = s->cirrus_blt_bgcol;
    colors[1] = s->cirrus_blt_fgcol;
    for(y = 0; y < bltheight; y++) {
        bitmask = 0x80 >> srcskipleft;
        bits = *src++;
        addr = dstaddr + dstskipleft;
        for (x = dstskipleft; x < bltwidth; x += (DEPTH / 8)) {
            if ((bitmask & 0xff) == 0) {
                bitmask = 0x80;
                bits = *src++;
            }
            col = colors[!!(bits & bitmask)];
            PUTPIXEL(s, addr, col);
            addr += (DEPTH / 8);
            bitmask >>= 1;
        }
        dstaddr += dstpitch;
    }
}