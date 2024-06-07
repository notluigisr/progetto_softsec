void HeaderMapImpl::setCopy(const LowerCaseString& key, absl::string_view value) {
  
  
  auto* entry = getExisting(key);
  if (entry) {
    updateSize(entry->value().size(), value.size());
    entry->value(value);
  } else {
    addCopy(key, value);
  }
}