load_uint(const void *val, size_t size)
{
    switch (size) {
    case 1: return *(uint8_t *)val;
    case 2: return *(uint16_t *)val;
    case 4: return *(uint32_t *)val;
    case 8: return *(uint64_t *)val;
    default: abort();
    }
}