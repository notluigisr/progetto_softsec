alloc_open_clump(gs_ref_memory_t * mem)
{
#ifdef DEBUG
    if (gs_debug_c('A')) {
        dmlprintf1((const gs_memory_t *)mem, "STR", alloc_trace_space(mem));
        dmprintf_clump((const gs_memory_t *)mem, "STR", mem->cc);
    }
#endif
}