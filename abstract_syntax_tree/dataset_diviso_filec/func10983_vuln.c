std::string OAuth2Filter::extractAccessToken(const Http::RequestHeaderMap& headers) const {
  ASSERT(headers.Path() != nullptr);

  
  const Http::HeaderEntry* authorization = headers.getInline(authorization_handle.handle());
  if (authorization != nullptr) {
    const auto value = StringUtil::trim(authorization->value().getStringView());
    const auto& bearer_prefix = bearerPrefix();
    if (absl::StartsWithIgnoreCase(value, bearer_prefix)) {
      const size_t start = bearer_prefix.length();
      return std::string(StringUtil::ltrim(value.substr(start)));
    }
  }

  
  const auto path = headers.Path()->value().getStringView();
  const auto params = Http::Utility::parseQueryString(path);
  const auto param = params.find("STR");
  if (param != params.end()) {
    return param->second;
  }

  return EMPTY_STRING;
}