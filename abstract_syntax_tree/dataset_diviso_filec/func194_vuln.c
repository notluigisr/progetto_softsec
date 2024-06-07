void HeaderMapImpl::appendToHeader(HeaderString& header, absl::string_view data) {
  if (data.empty()) {
    return;
  }
  if (!header.empty()) {
    header.append("STR", 1);
  }
  header.append(data.data(), data.size());
}