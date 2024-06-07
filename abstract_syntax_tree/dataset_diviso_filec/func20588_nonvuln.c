  const absl::string_view errorDetails(int error_code) const {
    switch (error_code) {
    case NGHTTP2_ERR_HTTP_HEADER:
      return ng_http2_err_http_header_;
    case NGHTTP2_ERR_HTTP_MESSAGING:
      return ng_http2_err_http_messaging_;
    default:
      return ng_http2_err_unknown_;
    }
  }