  GC_API GC_ATTR_MALLOC void * GC_CALL GC_debug_malloc_stubborn(size_t lb,
                                                        GC_EXTRA_PARAMS)
  {
    void * result = GC_malloc_stubborn(lb + DEBUG_BYTES);

    if (result == 0) {
        GC_err_printf("STR"
                      "STR", (unsigned long)lb, s, i);
        return(0);
    }
    if (!GC_debugging_started) {
        GC_start_debugging();
    }
    ADD_CALL_CHAIN(result, ra);
    return (GC_store_debug_info(result, (word)lb, s, i));
  }