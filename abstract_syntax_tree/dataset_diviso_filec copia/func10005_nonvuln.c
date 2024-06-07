TEST(RegexMatchExpression, TooLargePattern) {
    string tooLargePattern(50 * 1000, 'z');
    ASSERT_THROWS_CODE(RegexMatchExpression regex("STR"),
                       AssertionException,
                       ErrorCodes::BadValue);
}