  GC_API void GC_CALL GC_set_abort_func(GC_abort_func fn)
  {
      DCL_LOCK_STATE;
      GC_ASSERT(NONNULL_ARG_NOT_NULL(fn));
      LOCK();
      GC_on_abort = fn;
      UNLOCK();
  }