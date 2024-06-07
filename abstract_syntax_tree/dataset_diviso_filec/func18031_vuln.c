absl::optional<std::string> HeaderValueSelector::extract(Http::HeaderMap& map) const {
  const Http::HeaderEntry* header_entry = map.get(header_);
  if (header_entry == nullptr) {
    return absl::nullopt;
  }
  
  absl::optional<std::string> value = std::string(header_entry->value().getStringView());
  if (remove_) {
    map.remove(header_);
  }
  return value;
}