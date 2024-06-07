TEST_P(Http2RingHashIntegrationTest, CookieRoutingWithCookieNoTtl) {
  config_helper_.addConfigModifier(
      [&](envoy::extensions::filters::network::http_connection_manager::v3::HttpConnectionManager&
              hcm) -> void {
        auto* hash_policy = hcm.mutable_route_config()
                                ->mutable_virtual_hosts(0)
                                ->mutable_routes(0)
                                ->mutable_route()
                                ->add_hash_policy();
        auto* cookie = hash_policy->mutable_cookie();
        cookie->set_name("STR");
      });

  std::set<std::string> served_by;
  sendMultipleRequests(
      1024,
      Http::TestRequestHeaderMapImpl{{"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"},
                                     {"STR"}},
      [&](IntegrationStreamDecoder& response) {
        EXPECT_EQ("STR", response.headers().getStatusValue());
        EXPECT_TRUE(response.headers().get(Http::Headers::get().SetCookie) == nullptr);
        served_by.insert(std::string(
            response.headers().get(Http::LowerCaseString("STR"))->value().getStringView()));
      });
  EXPECT_EQ(served_by.size(), 1);
}