void OwnedImpl::coalesceOrAddSlice(SlicePtr&& other_slice) {
  const uint64_t slice_size = other_slice->dataSize();
  
  
  
  
  
  
  if (other_slice->canCoalesce() && !slices_.empty() && slice_size < CopyThreshold &&
      slices_.back()->reservableSize() >= slice_size) {
    
    
    addImpl(other_slice->data(), slice_size);
  } else {
    
    slices_.emplace_back(std::move(other_slice));
    length_ += slice_size;
  }
}