  void maybeAllocTrailers() override {
    ASSERT(processing_trailers_);
    if (!absl::holds_alternative<ResponseTrailerMapPtr>(headers_or_trailers_)) {
      headers_or_trailers_.emplace<ResponseTrailerMapPtr>(ResponseTrailerMapImpl::create());
    }
  }