TEST(Url, ParsingForConnectTest) {
  validateConnectUrl("STR", 443);
  validateConnectUrl("STR", 80);
}