  STATIC ptr_t GC_least_described_address(ptr_t start)
  {
    MEMORY_BASIC_INFORMATION buf;
    size_t result;
    LPVOID limit;
    ptr_t p;
    LPVOID q;

    limit = GC_sysinfo.lpMinimumApplicationAddress;
    p = (ptr_t)((word)start & ~(GC_page_size - 1));
    for (;;) {
        q = (LPVOID)(p - GC_page_size);
        if ((word)q > (word)p  || (word)q < (word)limit) break;
        result = VirtualQuery(q, &buf, sizeof(buf));
        if (result != sizeof(buf) || buf.AllocationBase == 0) break;
        p = (ptr_t)(buf.AllocationBase);
    }
    return p;
  }