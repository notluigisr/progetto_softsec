GC_API GC_ATTR_MALLOC void * GC_CALL GC_debug_gcj_malloc(size_t lb,
                void * ptr_to_struct_containing_descr, GC_EXTRA_PARAMS)
{
    void * result;
    DCL_LOCK_STATE;

    
    
    LOCK();
    maybe_finalize();
    result = GC_generic_malloc_inner(SIZET_SAT_ADD(lb, DEBUG_BYTES),
                                     GC_gcj_debug_kind);
    if (result == 0) {
        GC_oom_func oom_fn = GC_oom_fn;
        UNLOCK();
        GC_err_printf("STR",
                (unsigned long)lb, ptr_to_struct_containing_descr, s, i);
        return((*oom_fn)(lb));
    }
    *((void **)((ptr_t)result + sizeof(oh))) = ptr_to_struct_containing_descr;
    UNLOCK();
    if (!GC_debugging_started) {
        GC_start_debugging();
    }
    ADD_CALL_CHAIN(result, ra);
    return (GC_store_debug_info(result, (word)lb, s, i));
}