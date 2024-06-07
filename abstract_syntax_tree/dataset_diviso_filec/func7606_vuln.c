unique_ptr<IOBuf> IOBuf::create(std::size_t capacity) {
  
  
  
  
  
  
  
  
  
  if (capacity <= kDefaultCombinedBufSize) {
    return createCombined(capacity);
  }

  
  
  
  if (canNallocx()) {
    auto mallocSize = goodMallocSize(capacity);
    
    size_t minSize = ((capacity + 7) & ~7) + sizeof(SharedInfo);
    
    if (mallocSize < minSize) {
      auto* buf = checkedMalloc(mallocSize);
      return takeOwnership(SIZED_FREE, buf, mallocSize, 0, 0);
    }
  }

  return createSeparate(capacity);
}