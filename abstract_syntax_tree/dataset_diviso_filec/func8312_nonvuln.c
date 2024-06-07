extern "STR" void free_wrapper(void *ptr, void *caller)
{
#ifdef MBED_MEM_TRACING_ENABLED
    mbed_mem_trace_lock();
#endif
#ifdef MBED_HEAP_STATS_ENABLED
    malloc_stats_mutex->lock();
    alloc_info_t *alloc_info = NULL;
    if (ptr != NULL) {
        alloc_info = ((alloc_info_t *)ptr) - 1;
        if (MBED_HEAP_STATS_SIGNATURE == alloc_info->signature) {
            size_t user_size = alloc_info->size;
            size_t alloc_size = MALLOC_HEAP_TOTAL_SIZE(MALLOC_HEADER_PTR(alloc_info));
            alloc_info->signature = 0x0;
            heap_stats.current_size -= user_size;
            heap_stats.alloc_cnt -= 1;
            heap_stats.overhead_size -= (alloc_size - user_size);
            SUPER_FREE((void *)alloc_info);
        } else {
            SUPER_FREE(ptr);
        }
    }

    malloc_stats_mutex->unlock();
#else 
    SUPER_FREE(ptr);
#endif 
#ifdef MBED_MEM_TRACING_ENABLED
    mbed_mem_trace_free(ptr, caller);
    mbed_mem_trace_unlock();
#endif 
}