void HeaderMapImpl::addViaMove(HeaderString&& key, HeaderString&& value) {
  
  
  auto* entry = getExistingInline(key.getStringView());
  if (entry != nullptr) {
    appendToHeader(entry->value(), value.getStringView());
    key.clear();
    value.clear();
  } else {
    insertByKey(std::move(key), std::move(value));
  }
}