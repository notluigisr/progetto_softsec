  STATIC void GC_exit_check(void)
  {
    if (GC_find_leak) {
      GC_gcollect();
    }
  }