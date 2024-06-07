     (CirrusVGAState * s, uint8_t * dst,
      const uint8_t * src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint32_t colors[2];
    uint8_t *d;
    int x, y, bitpos, pattern_y;
    unsigned int bits;
    unsigned int col;
    int srcskipleft = s->vga.gr[0x2f] & 0x07;
    int dstskipleft = srcskipleft * (DEPTH / 8);

    colors[0] = s->cirrus_blt_bgcol;
    colors[1] = s->cirrus_blt_fgcol;
    pattern_y = s->cirrus_blt_srcaddr & 7;

    for(y = 0; y < bltheight; y++) {
        bits = src[pattern_y];
        bitpos = 7 - srcskipleft;
        d = dst + dstskipleft;
        for (x = dstskipleft; x < bltwidth; x += (DEPTH / 8)) {
            col = colors[(bits >> bitpos) & 1];
            PUTPIXEL();
            d += (DEPTH / 8);
            bitpos = (bitpos - 1) & 7;
        }
        pattern_y = (pattern_y + 1) & 7;
        dst += dstpitch;
    }
}