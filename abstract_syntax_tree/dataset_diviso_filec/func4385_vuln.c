void validateUrl(absl::string_view raw_url, absl::string_view expected_scheme,
                 absl::string_view expected_host_port, absl::string_view expected_path,
                 uint16_t expected_port) {
  Utility::Url url;
  ASSERT_TRUE(url.initialize(raw_url, false)) << "STR" << raw_url;
  EXPECT_EQ(url.scheme(), expected_scheme);
  EXPECT_EQ(url.hostAndPort(), expected_host_port);
  EXPECT_EQ(url.pathAndQueryParams(), expected_path);
  EXPECT_EQ(url.port(), expected_port);
}