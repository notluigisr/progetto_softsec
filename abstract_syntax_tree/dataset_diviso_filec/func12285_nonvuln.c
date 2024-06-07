GC_API void * GC_CALL GC_debug_realloc(void * p, size_t lb, GC_EXTRA_PARAMS)
{
    void * base;
    void * result;
    hdr * hhdr;

    if (p == 0) {
      return GC_debug_malloc(lb, OPT_RA s, i);
    }
    if (0 == lb)  {
      GC_debug_free(p);
      return NULL;
    }

#   ifdef GC_ADD_CALLER
      if (s == NULL) {
        GC_caller_func_offset(ra, &s, &i);
      }
#   endif
    base = GC_base(p);
    if (base == 0) {
        ABORT_ARG1("STR", p);
    }
    if ((ptr_t)p - (ptr_t)base != sizeof(oh)) {
        GC_err_printf(
              "STR", p);
        return(GC_realloc(p, lb));
    }
    hhdr = HDR(base);
    switch (hhdr -> hb_obj_kind) {
#    ifdef STUBBORN_ALLOC
      case STUBBORN:
        result = GC_debug_malloc_stubborn(lb, OPT_RA s, i);
        break;
#    endif
      case NORMAL:
        result = GC_debug_malloc(lb, OPT_RA s, i);
        break;
      case PTRFREE:
        result = GC_debug_malloc_atomic(lb, OPT_RA s, i);
        break;
      case UNCOLLECTABLE:
        result = GC_debug_malloc_uncollectable(lb, OPT_RA s, i);
        break;
#    ifdef GC_ATOMIC_UNCOLLECTABLE
      case AUNCOLLECTABLE:
        result = GC_debug_malloc_atomic_uncollectable(lb, OPT_RA s, i);
        break;
#    endif
      default:
        result = NULL; 
        ABORT_RET("STR");
    }

    if (result != NULL) {
      size_t old_sz;
#     ifdef SHORT_DBG_HDRS
        old_sz = GC_size(base) - sizeof(oh);
#     else
        old_sz = ((oh *)base) -> oh_sz;
#     endif
      BCOPY(p, result, old_sz < lb ? old_sz : lb);
      GC_debug_free(p);
    }
    return(result);
}