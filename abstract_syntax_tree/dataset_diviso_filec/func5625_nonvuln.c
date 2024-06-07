TEST_F(ExprMatchTest, LtWithLHSFieldPathMatchesCorrectly) {
    createMatcher(fromjson("STR"));

    ASSERT_TRUE(matches(BSON("STR" << 1)));

    ASSERT_FALSE(matches(BSON("STR" << 3)));
    ASSERT_FALSE(matches(BSON("STR" << 10)));
}