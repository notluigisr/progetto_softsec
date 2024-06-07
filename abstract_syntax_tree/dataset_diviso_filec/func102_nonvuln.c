  RequestOrResponseHeaderMap& requestOrResponseHeaders() override {
    return *absl::get<ResponseHeaderMapPtr>(headers_or_trailers_);
  }