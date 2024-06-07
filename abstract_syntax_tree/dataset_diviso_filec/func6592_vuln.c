     (CirrusVGAState *s, uint32_t dstaddr,
      const uint8_t *src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint32_t addr;
    int x, y, bitpos, pattern_y;
    unsigned int bits, bits_xor;
    unsigned int col;
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
    pattern_y = s->cirrus_blt_srcaddr & 7;

    for(y = 0; y < bltheight; y++) {
        bits = src[pattern_y] ^ bits_xor;
        bitpos = 7 - srcskipleft;
        addr = dstaddr + dstskipleft;
        for (x = dstskipleft; x < bltwidth; x += (DEPTH / 8)) {
            if ((bits >> bitpos) & 1) {
                PUTPIXEL(s, addr, col);
            }
            addr += (DEPTH / 8);
            bitpos = (bitpos - 1) & 7;
        }
        pattern_y = (pattern_y + 1) & 7;
        dstaddr += dstpitch;
    }
}