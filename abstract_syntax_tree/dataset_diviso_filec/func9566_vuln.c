  void allocHeaders() override {
    ASSERT(nullptr == absl::get<ResponseHeaderMapPtr>(headers_or_trailers_));
    headers_or_trailers_.emplace<ResponseHeaderMapPtr>(ResponseHeaderMapImpl::create());
  }