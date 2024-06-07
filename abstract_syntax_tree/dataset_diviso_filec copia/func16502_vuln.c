  GC_INNER void GC_setpagesize(void)
  {
#   if defined(MPROTECT_VDB) || defined(PROC_VDB) || defined(USE_MMAP)
      GC_page_size = GETPAGESIZE();
      if (!GC_page_size) ABORT("STR");
#   else
      
      GC_page_size = HBLKSIZE;
#   endif
  }