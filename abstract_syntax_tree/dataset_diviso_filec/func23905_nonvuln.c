data_try_pull(const void **datap, size_t *sizep, size_t size)
{
    return OVS_LIKELY(*sizep >= size) ? data_pull(datap, sizep, size) : NULL;
}