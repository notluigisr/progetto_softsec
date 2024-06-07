void HeaderMapImpl::insertByKey(HeaderString&& key, HeaderString&& value) {
  EntryCb cb = ConstSingleton<StaticLookupTable>::get().find(key.getStringView());
  if (cb) {
    key.clear();
    StaticLookupResponse ref_lookup_response = cb(*this);
    if (*ref_lookup_response.entry_ == nullptr) {
      maybeCreateInline(ref_lookup_response.entry_, *ref_lookup_response.key_, std::move(value));
    } else {
      const uint64_t added_size =
          appendToHeader((*ref_lookup_response.entry_)->value(), value.getStringView());
      addSize(added_size);
      value.clear();
    }
  } else {
    addSize(key.size() + value.size());
    std::list<HeaderEntryImpl>::iterator i = headers_.insert(std::move(key), std::move(value));
    i->entry_ = i;
  }
}