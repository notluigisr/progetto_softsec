     (CirrusVGAState *s,
      uint8_t *dst, int dst_pitch,
      int width, int height)
{
    uint8_t *d, *d1;
    uint32_t col;
    int x, y;

    col = s->cirrus_blt_fgcol;

    d1 = dst;
    for(y = 0; y < height; y++) {
        d = d1;
        for(x = 0; x < width; x += (DEPTH / 8)) {
            PUTPIXEL();
            d += (DEPTH / 8);
        }
        d1 += dst_pitch;
    }
}