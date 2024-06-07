TEST_F(ExprMatchTest, GteWithLHSFieldPathMatchesCorrectly) {
    createMatcher(fromjson("STR"));

    ASSERT_TRUE(matches(BSON("STR" << 3)));
    ASSERT_TRUE(matches(BSON("STR" << 10)));

    ASSERT_FALSE(matches(BSON("STR" << 1)));
}