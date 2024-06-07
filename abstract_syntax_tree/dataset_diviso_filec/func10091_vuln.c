bool Url::initialize(absl::string_view absolute_url, bool is_connect) {
  
  
  GURL parsed(std::string{absolute_url});
  if (is_connect) {
    return initializeForConnect(std::move(parsed));
  }

  
  
  if (!parsed.is_valid() || !parsed.SchemeIsHTTPOrHTTPS()) {
    return false;
  }

  scheme_ = parsed.scheme();

  
  
  
  
  host_and_port_ =
      absl::StrCat(parsed.host(), parsed.has_port() ? "STR" : EMPTY_STRING, parsed.port());

  const int port = parsed.EffectiveIntPort();
  if (port <= 0 || port > std::numeric_limits<uint16_t>::max()) {
    return false;
  }
  port_ = static_cast<uint16_t>(port);

  
  path_and_query_params_ = parsed.PathForRequest();
  if (parsed.has_ref()) {
    absl::StrAppend(&path_and_query_params_, "STR", parsed.ref());
  }

  return true;
}