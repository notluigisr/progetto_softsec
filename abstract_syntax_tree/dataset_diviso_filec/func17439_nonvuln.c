IOBuf::SharedInfo::SharedInfo(FreeFunction fn, void* arg, bool hfs)
    : freeFn(fn), userData(arg), useHeapFullStorage(hfs) {
  
  
  refcount.store(1, std::memory_order_relaxed);
}