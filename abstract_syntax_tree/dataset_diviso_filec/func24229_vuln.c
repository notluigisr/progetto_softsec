  void maybeAllocTrailers() override {
    ASSERT(processing_trailers_);
    if (!absl::holds_alternative<RequestTrailerMapPtr>(headers_or_trailers_)) {
      headers_or_trailers_.emplace<RequestTrailerMapPtr>(RequestTrailerMapImpl::create());
    }
  }