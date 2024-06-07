     (CirrusVGAState * s, uint8_t * dst,
      const uint8_t * src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint32_t colors[2];
    uint8_t *d;
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
        d = dst + dstskipleft;
        for (x = dstskipleft; x < bltwidth; x += (DEPTH / 8)) {
            if ((bitmask & 0xff) == 0) {
                bitmask = 0x80;
                bits = *src++;
            }
            col = colors[!!(bits & bitmask)];
            PUTPIXEL();
            d += (DEPTH / 8);
            bitmask >>= 1;
        }
        dst += dstpitch;
    }
}