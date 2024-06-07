static bool is_sst_request_valid(const std::string &msg) {
  size_t method_len = strlen(msg.c_str());

  if (method_len == 0) {
    return false;
  }

  std::string method = msg.substr(0, method_len);

  
  auto res = std::find(std::begin(allowed_sst_methods),
                       std::end(allowed_sst_methods), method);
  if (res == std::end(allowed_sst_methods)) {
    return false;
  }

  const char *data_ptr = msg.c_str() + method_len + 1;
  size_t data_len = strlen(data_ptr);

  
  if (method_len + 1 + data_len + 1 != msg.length()) {
    
    return false;
  }

  if (data_len > 0) {
    
    std::string data = msg.substr(method_len + 1, data_len);
    static const std::regex allowed_chars_regex("STR");
    if (!std::regex_match(data, allowed_chars_regex)) {
      return false;
    }
  }
  return true;
}