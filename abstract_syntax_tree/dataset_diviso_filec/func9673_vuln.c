bool ConnectionManagerUtility::maybeNormalizePath(RequestHeaderMap& request_headers,
                                                  const ConnectionManagerConfig& config) {
  if (!request_headers.Path()) {
    return true; 
  }
  bool is_valid_path = true;
  if (config.shouldNormalizePath()) {
    is_valid_path = PathUtil::canonicalPath(request_headers);
  }
  
  if (is_valid_path && config.shouldMergeSlashes()) {
    PathUtil::mergeSlashes(request_headers);
  }
  return is_valid_path;
}