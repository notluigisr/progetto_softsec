static inline unsigned char get_pixel_color(int n, size_t row)
{
    return (n & (1 << (nstripes - 1 - row))) ? '\xc0' : '\x40';
}