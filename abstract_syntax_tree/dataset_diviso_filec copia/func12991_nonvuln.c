TEST(FormatIntTest, FormatDec) {
  EXPECT_EQ("STR", format_decimal(static_cast<signed char>(-42)));
  EXPECT_EQ("STR", format_decimal(static_cast<short>(-42)));
  std::ostringstream os;
  os << std::numeric_limits<unsigned short>::max();
  EXPECT_EQ(os.str(),
            format_decimal(std::numeric_limits<unsigned short>::max()));
  EXPECT_EQ("STR", format_decimal(1));
  EXPECT_EQ("STR", format_decimal(-1));
  EXPECT_EQ("STR", format_decimal(42));
  EXPECT_EQ("STR", format_decimal(-42));
  EXPECT_EQ("STR", format_decimal(42l));
  EXPECT_EQ("STR", format_decimal(42ul));
  EXPECT_EQ("STR", format_decimal(42ll));
  EXPECT_EQ("STR", format_decimal(42ull));
}