vterm_malloc(size_t size, void *data UNUSED)
{
    return alloc_clear((unsigned) size);
}