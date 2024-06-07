     (CirrusVGAState * s, uint8_t * dst,
      const uint8_t * src,
      int dstpitch, int srcpitch,
      int bltwidth, int bltheight)
{
    uint8_t *d;
    int x, y, pattern_y, pattern_pitch, pattern_x;
    unsigned int col;
    const uint8_t *src1;
#if DEPTH == 24
    int skipleft = s->vga.gr[0x2f] & 0x1f;
#else
    int skipleft = (s->vga.gr[0x2f] & 0x07) * (DEPTH / 8);
#endif

#if DEPTH == 8
    pattern_pitch = 8;
#elif DEPTH == 16
    pattern_pitch = 16;
#else
    pattern_pitch = 32;
#endif
    pattern_y = s->cirrus_blt_srcaddr & 7;
    for(y = 0; y < bltheight; y++) {
        pattern_x = skipleft;
        d = dst + skipleft;
        src1 = src + pattern_y * pattern_pitch;
        for (x = skipleft; x < bltwidth; x += (DEPTH / 8)) {
#if DEPTH == 8
            col = src1[pattern_x];
            pattern_x = (pattern_x + 1) & 7;
#elif DEPTH == 16
            col = ((uint16_t *)(src1 + pattern_x))[0];
            pattern_x = (pattern_x + 2) & 15;
#elif DEPTH == 24
            {
                const uint8_t *src2 = src1 + pattern_x * 3;
                col = src2[0] | (src2[1] << 8) | (src2[2] << 16);
                pattern_x = (pattern_x + 1) & 7;
            }
#else
            col = ((uint32_t *)(src1 + pattern_x))[0];
            pattern_x = (pattern_x + 4) & 31;
#endif
            PUTPIXEL();
            d += (DEPTH / 8);
        }
        pattern_y = (pattern_y + 1) & 7;
        dst += dstpitch;
    }
}