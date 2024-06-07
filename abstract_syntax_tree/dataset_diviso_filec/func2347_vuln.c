STATIC void * GC_debug_generic_malloc(size_t lb, int knd, GC_EXTRA_PARAMS)
{
    void * result = GC_generic_malloc(lb + DEBUG_BYTES, knd);

    if (NULL == result) {
        GC_err_printf(
                "STR",
                (unsigned long)lb, knd, s, i);
        return NULL;
    }
    if (!GC_debugging_started) {
        GC_start_debugging();
    }
    ADD_CALL_CHAIN(result, ra);
    return GC_store_debug_info(result, (word)lb, s, i);
}