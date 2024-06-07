ptr_t GC_unix_get_mem(word bytes)
{
# if defined(MMAP_SUPPORTED)
    
    static GC_bool sbrk_failed = FALSE;
    ptr_t result = 0;

    if (!sbrk_failed) result = GC_unix_sbrk_get_mem(bytes);
    if (0 == result) {
        sbrk_failed = TRUE;
        result = GC_unix_mmap_get_mem(bytes);
    }
    if (0 == result) {
        
        result = GC_unix_sbrk_get_mem(bytes);
    }
    return result;
# else 
    return GC_unix_sbrk_get_mem(bytes);
# endif
}