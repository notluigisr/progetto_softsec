  bool matches(const Http::RequestHeaderMap& headers) const override {
    if (BaseMatcherImpl::matchRoute(headers)) {
      const Http::HeaderString& path = headers.Path()->value();
      const absl::string_view query_string = Http::Utility::findQueryStringStart(path);
      absl::string_view path_view = path.getStringView();
      path_view.remove_suffix(query_string.length());
      if (path_matcher_->match(path_view)) {
        ENVOY_LOG(debug, "STR", regex_str_);
        return true;
      }
    }
    return false;
  }