size_t IOBuf::goodExtBufferSize(std::size_t minCapacity) {
  
  
  
  
  size_t minSize = static_cast<size_t>(minCapacity) + sizeof(SharedInfo);
  
  
  minSize = (minSize + 7) & ~7;

  
  
  
  return goodMallocSize(minSize);
}