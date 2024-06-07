     (CirrusVGAState *s, uint32_t dstaddr,
      const uint8_t *src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint32_t addr;
    int x, y;
    unsigned bits, bits_xor;
    unsigned int col;
    unsigned bitmask;
    unsigned index;
#if DEPTH == 24
    int dstskipleft = s->vga.gr[0x2f] & 0x1f;
    int srcskipleft = dstskipleft / 3;
#else
    int srcskipleft = s->vga.gr[0x2f] & 0x07;
    int dstskipleft = srcskipleft * (DEPTH / 8);
#endif

    if (s->cirrus_blt_modeext & CIRRUS_BLTMODEEXT_COLOREXPINV) {
        bits_xor = 0xff;
        col = s->cirrus_blt_bgcol;
    } else {
        bits_xor = 0x00;
        col = s->cirrus_blt_fgcol;
    }

    for(y = 0; y < bltheight; y++) {
        bitmask = 0x80 >> srcskipleft;
        bits = *src++ ^ bits_xor;
        addr = dstaddr + dstskipleft;
        for (x = dstskipleft; x < bltwidth; x += (DEPTH / 8)) {
            if ((bitmask & 0xff) == 0) {
                bitmask = 0x80;
                bits = *src++ ^ bits_xor;
            }
            index = (bits & bitmask);
            if (index) {
                PUTPIXEL(s, addr, col);
            }
            addr += (DEPTH / 8);
            bitmask >>= 1;
        }
        dstaddr += dstpitch;
    }
}