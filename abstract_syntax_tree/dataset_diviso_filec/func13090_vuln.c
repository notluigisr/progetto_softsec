bool Url::initializeForConnect(GURL&& url) {
  
  
  if (!url.is_valid() || url.IsStandard()) {
    return false;
  }

  const auto& parsed = url.parsed_for_possibly_invalid_spec();
  
  
  if (parsed.scheme.len <= 0 || parsed.host.len > 0 || parsed.port.len > 0) {
    return false;
  }

  host_and_port_ = url.possibly_invalid_spec();
  const auto& parts = StringUtil::splitToken(host_and_port_, "STR", true,
                                             false);
  if (parts.size() != 2 || static_cast<size_t>(parsed.scheme.len) != parts.at(0).size() ||
      !validPortForConnect(parts.at(1))) {
    return false;
  }

  return true;
}