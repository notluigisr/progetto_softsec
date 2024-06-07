  GC_API GC_ATTR_MALLOC void * GC_CALL GC_debug_malloc_stubborn(size_t lb,
                                                        GC_EXTRA_PARAMS)
  {
    return GC_debug_malloc(lb, OPT_RA s, i);
  }