  ptr_t GC_unix_get_mem(word bytes)
  {
    return GC_unix_mmap_get_mem(bytes);
  }