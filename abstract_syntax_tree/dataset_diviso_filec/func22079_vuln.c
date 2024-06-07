inline void* Zone::New(int size) {
  ASSERT(scope_nesting_ > 0);
  
  size = RoundUp(size, kAlignment);

  
  
  if (kPointerSize == 4 && kAlignment == 4) {
    position_ += ((~size) & 4) & (reinterpret_cast<intptr_t>(position_) & 4);
  } else {
    ASSERT(kAlignment >= kPointerSize);
  }

  
  Address result = position_;

  if (size > limit_ - position_) {
     result = NewExpand(size);
  } else {
     position_ += size;
  }

  
  ASSERT(IsAddressAligned(result, kAlignment, 0));
  allocation_size_ += size;
  return reinterpret_cast<void*>(result);
}