    GC_malloc_explicitly_typed_ignore_off_page(size_t lb, GC_descr d)
{
    ptr_t op;
    size_t lg;
    DCL_LOCK_STATE;

    GC_ASSERT(GC_explicit_typing_initialized);
    lb += TYPD_EXTRA_BYTES;
    if (SMALL_OBJ(lb)) {
        GC_DBG_COLLECT_AT_MALLOC(lb);
        lg = GC_size_map[lb];
        LOCK();
        op = GC_eobjfreelist[lg];
        if (EXPECT(0 == op, FALSE)) {
            UNLOCK();
            op = (ptr_t)GENERAL_MALLOC_IOP(lb, GC_explicit_kind);
            if (0 == op) return 0;
            lg = GC_size_map[lb];       
        } else {
            GC_eobjfreelist[lg] = obj_link(op);
            obj_link(op) = 0;
            GC_bytes_allocd += GRANULES_TO_BYTES(lg);
            UNLOCK();
        }
        ((word *)op)[GRANULES_TO_WORDS(lg) - 1] = d;
   } else {
       op = (ptr_t)GENERAL_MALLOC_IOP(lb, GC_explicit_kind);
       if (op != NULL) {
         lg = BYTES_TO_GRANULES(GC_size(op));
         ((word *)op)[GRANULES_TO_WORDS(lg) - 1] = d;
       }
   }
   return((void *) op);
}