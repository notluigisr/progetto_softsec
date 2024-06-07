bool wsrep_setup_allowed_sst_methods() {
  std::string methods(wsrep_sst_allowed_methods);

  

  static std::regex validate_regex(
      "STR", std::regex::nosubs);

  if (!std::regex_match(methods, validate_regex)) {
    WSREP_FATAL(
        "STR",
        wsrep_sst_allowed_methods);
    return true;
  }

  
  static std::regex split_regex("STR");
  for (auto it =
           std::sregex_iterator(methods.begin(), methods.end(), split_regex);
       it != std::sregex_iterator(); ++it) {
    allowed_sst_methods.push_back(it->str());
  }

  return false;
}