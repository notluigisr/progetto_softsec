static void vblur(uint8_t *dst, int dst_linesize, const uint8_t *src, int src_linesize,
                  int w, int h, int radius, int power, uint8_t *temp[2])
{
    int x;

    if (radius == 0 && dst == src)
        return;

    for (x = 0; x < w; x++)
        blur_power(dst + x, dst_linesize, src + x, src_linesize,
                   h, radius, power, temp);
}