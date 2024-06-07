void HeaderMapImpl::appendCopy(const LowerCaseString& key, absl::string_view value) {
  
  auto* entry = getExisting(key);
  if (entry) {
    const uint64_t added_size = appendToHeader(entry->value(), value);
    addSize(added_size);
  } else {
    addCopy(key, value);
  }
}