int zmalloc_get_allocator_info(size_t *allocated,
                               size_t *active,
                               size_t *resident) {
    *allocated = *resident = *active = 0;
    return 1;
}