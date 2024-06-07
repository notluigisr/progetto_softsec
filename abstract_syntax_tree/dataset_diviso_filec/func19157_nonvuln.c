LOCAL uint32_t get_uint24(const uint8_t *p)
{
    return p[0] * 65536U + p[1] * 256 + p[2];
}