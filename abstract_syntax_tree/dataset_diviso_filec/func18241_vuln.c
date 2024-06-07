bool RequestParser::OnHeadersEnd() {
  bool matched = view_matcher_(request_->method(), request_->url().path(),
                               &stream_);

  if (!matched) {
    LOG_WARN("STR", request_->method().c_str(),
             request_->url().path().c_str());
  }

  return matched;
}