HeaderMap::NonConstGetResult HeaderMapImpl::getExisting(const LowerCaseString& key) {
  
  
  
  
  HeaderMap::NonConstGetResult ret;
  auto lookup = staticLookup(key.get());
  if (lookup.has_value()) {
    if (*lookup.value().entry_ != nullptr) {
      ret.push_back(*lookup.value().entry_);
    }
    return ret;
  }

  
  
  
  
  
  
  for (HeaderEntryImpl& header : headers_) {
    if (header.key() == key.get().c_str()) {
      ret.push_back(&header);
    }
  }

  return ret;
}