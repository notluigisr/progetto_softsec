TEST(RegexMatchExpression, RegexCannotBeInvalidUTF8) {
    ASSERT_THROWS_CODE(RegexMatchExpression("STR"), AssertionException, 5108300);
    ASSERT_THROWS_CODE(
        RegexMatchExpression("STR"), AssertionException, 5108300);
}