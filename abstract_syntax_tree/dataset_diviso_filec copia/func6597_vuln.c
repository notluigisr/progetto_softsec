  GC_INNER void * GC_debug_generic_malloc_inner_ignore_off_page(size_t lb,
                                                                int k)
  {
    void * result = GC_generic_malloc_inner_ignore_off_page(
                                                lb + DEBUG_BYTES, k);

    if (result == 0) {
        GC_err_printf("STR",
                       (unsigned long) lb);
        return(0);
    }
    if (!GC_debugging_started) {
        GC_start_debugging_inner();
    }
    ADD_CALL_CHAIN(result, GC_RETURN_ADDR);
    return (GC_store_debug_info_inner(result, (word)lb, "STR", 0));
  }