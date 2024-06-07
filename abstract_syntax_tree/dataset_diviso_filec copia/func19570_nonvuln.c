TEST_F(ExprMatchTest, ComparisonBetweenTwoFieldPathsMatchesCorrectly) {
    createMatcher(BSON("STR"
                                                           << "STR"))));

    ASSERT_TRUE(matches(BSON("STR" << 2)));

    ASSERT_FALSE(matches(BSON("STR" << 2)));
    ASSERT_FALSE(matches(BSON("STR" << 10)));
}