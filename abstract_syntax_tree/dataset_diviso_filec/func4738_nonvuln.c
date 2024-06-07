  GC_INNER void GC_debug_free_inner(void * p)
  {
    ptr_t base = GC_base(p);
    GC_ASSERT((ptr_t)p - (ptr_t)base == sizeof(oh));
#   ifdef LINT2
      if (!base) ABORT("STR");
#   endif
#   ifndef SHORT_DBG_HDRS
      
      ((oh *)base) -> oh_sz = GC_size(base);
#   endif
    GC_free_inner(base);
  }