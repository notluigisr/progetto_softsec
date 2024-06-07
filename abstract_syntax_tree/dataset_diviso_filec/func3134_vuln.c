Address Zone::NewExpand(int size) {
  
  
  ASSERT(size == RoundDown(size, kAlignment));
  ASSERT(size > limit_ - position_);

  
  
  
  
  Segment* head = segment_head_;
  int old_size = (head == NULL) ? 0 : head->size();
  static const int kSegmentOverhead = sizeof(Segment) + kAlignment;
  int new_size_no_overhead = size + (old_size << 1);
  int new_size = kSegmentOverhead + new_size_no_overhead;
  
  if (new_size_no_overhead < size || new_size < kSegmentOverhead) {
    V8::FatalProcessOutOfMemory("STR");
    return NULL;
  }
  if (new_size < kMinimumSegmentSize) {
    new_size = kMinimumSegmentSize;
  } else if (new_size > kMaximumSegmentSize) {
    
    
    
    
    new_size = Max(kSegmentOverhead + size, kMaximumSegmentSize);
  }
  Segment* segment = NewSegment(new_size);
  if (segment == NULL) {
    V8::FatalProcessOutOfMemory("STR");
    return NULL;
  }

  
  Address result = RoundUp(segment->start(), kAlignment);
  position_ = result + size;
  
  if (position_ < result) {
    V8::FatalProcessOutOfMemory("STR");
    return NULL;
  }
  limit_ = segment->end();
  ASSERT(position_ <= limit_);
  return result;
}