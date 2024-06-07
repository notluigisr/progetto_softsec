extern "STR" void *malloc_wrapper(size_t size, void *caller)
{
    void *ptr = NULL;
#ifdef MBED_MEM_TRACING_ENABLED
    mbed_mem_trace_lock();
#endif
#ifdef MBED_HEAP_STATS_ENABLED
    malloc_stats_mutex->lock();
    alloc_info_t *alloc_info = (alloc_info_t *)SUPER_MALLOC(size + sizeof(alloc_info_t));
    if (alloc_info != NULL) {
        alloc_info->size = size;
        alloc_info->signature = MBED_HEAP_STATS_SIGNATURE;
        ptr = (void *)(alloc_info + 1);
        heap_stats.current_size += size;
        heap_stats.total_size += size;
        heap_stats.alloc_cnt += 1;
        if (heap_stats.current_size > heap_stats.max_size) {
            heap_stats.max_size = heap_stats.current_size;
        }
        heap_stats.overhead_size += MALLOC_HEAP_TOTAL_SIZE(MALLOC_HEADER_PTR(alloc_info)) - size;
    } else {
        heap_stats.alloc_fail_cnt += 1;
    }
    malloc_stats_mutex->unlock();
#else 
    ptr = SUPER_MALLOC(size);
#endif 
#ifdef MBED_MEM_TRACING_ENABLED
    mbed_mem_trace_malloc(ptr, size, caller);
    mbed_mem_trace_unlock();
#endif 
    return ptr;
}