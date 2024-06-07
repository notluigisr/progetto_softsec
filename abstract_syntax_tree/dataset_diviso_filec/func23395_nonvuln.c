void *hi_malloc_safe(size_t size) {
    void *ptr = hi_malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "STR");
        exit(-1);
    }

    return ptr;
}