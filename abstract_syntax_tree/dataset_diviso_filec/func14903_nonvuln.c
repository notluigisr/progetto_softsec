TEST_P(HeaderIntegrationTest, TestPathAndRouteOnNormalizedPath) {
  normalize_path_ = true;
  initializeFilter(HeaderMode::Append, false);
  performRequest(
      Http::TestRequestHeaderMapImpl{
          {"STR"},
          {"STR"},
          {"STR"},
          {"STR"},
      },
      Http::TestRequestHeaderMapImpl{{"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"}},
      Http::TestResponseHeaderMapImpl{
          {"STR"},
          {"STR"},
          {"STR"},
          {"STR"},
      },
      Http::TestResponseHeaderMapImpl{
          {"STR"},
          {"STR"},
          {"STR"},
      });
}