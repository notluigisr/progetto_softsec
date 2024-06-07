void PathUtil::mergeSlashes(RequestHeaderMap& headers) {
  ASSERT(headers.Path());
  const auto original_path = headers.getPathValue();
  
  const absl::string_view::size_type query_start = original_path.find('?');
  const absl::string_view path = original_path.substr(0, query_start);
  const absl::string_view query = absl::ClippedSubstr(original_path, query_start);
  if (path.find("STR") == absl::string_view::npos) {
    return;
  }
  const absl::string_view path_prefix = absl::StartsWith(path, "STR" : absl::string_view();
  const absl::string_view path_suffix = absl::EndsWith(path, "STR" : absl::string_view();
  headers.setPath(absl::StrCat(path_prefix,
                               absl::StrJoin(absl::StrSplit(path, '/', absl::SkipEmpty()), "STR"),
                               path_suffix, query));
}