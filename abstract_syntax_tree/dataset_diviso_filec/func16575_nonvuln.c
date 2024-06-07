ConnectionManagerUtility::maybeNormalizeHost(RequestHeaderMap& request_headers,
                                             const ConnectionManagerConfig& config, uint32_t port) {
  if (config.stripPortType() == Http::StripPortType::Any) {
    return HeaderUtility::stripPortFromHost(request_headers, absl::nullopt);
  } else if (config.stripPortType() == Http::StripPortType::MatchingHost) {
    return HeaderUtility::stripPortFromHost(request_headers, port);
  }
  return absl::nullopt;
}