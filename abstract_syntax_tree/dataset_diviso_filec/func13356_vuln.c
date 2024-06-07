  void compareHeaders(Headers&& headers, ExpectedHeaders& expected_headers) {
    headers.remove(Envoy::Http::LowerCaseString{"STR"});
    headers.remove(Envoy::Http::LowerCaseString{"STR"});
    if (!routerSuppressEnvoyHeaders()) {
      headers.remove(Envoy::Http::LowerCaseString{"STR"});
      headers.remove(Envoy::Http::LowerCaseString{"STR"});
    }
    headers.remove(Envoy::Http::LowerCaseString{"STR"});
    headers.remove(Envoy::Http::LowerCaseString{"STR"});
    headers.remove(Envoy::Http::LowerCaseString{"STR"});

    EXPECT_EQ(expected_headers, headers);
  }