  UTF16Ref getUTF16Ref(llvh::SmallVectorImpl<char16_t> &allocator) const {
    return getUTF16Ref(allocator, false);
  }