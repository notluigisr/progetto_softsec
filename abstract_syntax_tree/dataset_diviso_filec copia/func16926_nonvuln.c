TEST_F(ExprMatchTest, EqWithLHSFieldPathMatchesCorrectly) {
    createMatcher(fromjson("STR"));

    ASSERT_TRUE(matches(BSON("STR" << 3)));

    ASSERT_FALSE(matches(BSON("STR" << 1)));
    ASSERT_FALSE(matches(BSON("STR" << 10)));
}