bool Url::validPortForConnect(absl::string_view port_string) {
  int port;
  const bool valid = absl::SimpleAtoi(port_string, &port);
  
  if (!valid || port <= 0 || port > std::numeric_limits<uint16_t>::max()) {
    return false;
  }
  port_ = static_cast<uint16_t>(port);
  return true;
}