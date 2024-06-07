bool OwnedImpl::startsWith(absl::string_view data) const {
  if (length() < data.length()) {
    
    return false;
  }

  if (data.length() == 0) {
    return true;
  }

  const uint8_t* prefix = reinterpret_cast<const uint8_t*>(data.data());
  size_t size = data.length();
  for (const auto& slice : slices_) {
    uint64_t slice_size = slice->dataSize();
    const uint8_t* slice_start = slice->data();

    if (slice_size >= size) {
      
      return memcmp(prefix, slice_start, size) == 0;
    }

    
    if (memcmp(prefix, slice_start, slice_size) != 0) {
      return false;
    }

    
    prefix += slice_size;
    size -= slice_size;
  }

  
  NOT_REACHED_GCOVR_EXCL_LINE;
}