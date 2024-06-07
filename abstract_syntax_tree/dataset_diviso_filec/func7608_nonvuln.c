FilterUtility::StrictHeaderChecker::checkHeader(Http::HeaderMap& headers,
                                                const Http::LowerCaseString& target_header) {
  if (target_header == Http::Headers::get().EnvoyUpstreamRequestTimeoutMs) {
    return isInteger(headers.EnvoyUpstreamRequestTimeoutMs());
  } else if (target_header == Http::Headers::get().EnvoyUpstreamRequestPerTryTimeoutMs) {
    return isInteger(headers.EnvoyUpstreamRequestPerTryTimeoutMs());
  } else if (target_header == Http::Headers::get().EnvoyMaxRetries) {
    return isInteger(headers.EnvoyMaxRetries());
  } else if (target_header == Http::Headers::get().EnvoyRetryOn) {
    return hasValidRetryFields(headers.EnvoyRetryOn(), &Router::RetryStateImpl::parseRetryOn);
  } else if (target_header == Http::Headers::get().EnvoyRetryGrpcOn) {
    return hasValidRetryFields(headers.EnvoyRetryGrpcOn(),
                               &Router::RetryStateImpl::parseRetryGrpcOn);
  }
  
  NOT_REACHED_GCOVR_EXCL_LINE
}