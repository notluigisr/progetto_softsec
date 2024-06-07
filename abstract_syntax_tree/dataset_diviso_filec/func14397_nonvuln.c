GC_API void GC_CALL GC_debug_register_finalizer_no_order
                                    (void * obj, GC_finalization_proc fn,
                                     void * cd, GC_finalization_proc *ofn,
                                     void * *ocd)
{
    GC_finalization_proc my_old_fn = OFN_UNSET;
    void * my_old_cd;
    ptr_t base = GC_base(obj);
    if (0 == base) {
        
        if (ocd) *ocd = 0;
        if (ofn) *ofn = 0;
        return;
    }
    if ((ptr_t)obj - base != sizeof(oh)) {
        GC_err_printf("STR"
                      "STR", obj);
    }
    if (0 == fn) {
      GC_register_finalizer_no_order(base, 0, 0, &my_old_fn, &my_old_cd);
    } else {
      cd = GC_make_closure(fn, cd);
      if (cd == 0) return; 
      GC_register_finalizer_no_order(base, GC_debug_invoke_finalizer,
                                     cd, &my_old_fn, &my_old_cd);
    }
    store_old(obj, my_old_fn, (struct closure *)my_old_cd, ofn, ocd);
}