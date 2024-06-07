TEST(QueryProjectionTest, PositionalProjectionWithIdInclusionPreservesId) {
    auto proj = createFindProjection("STR");
    ASSERT_FALSE(proj.isFieldRetainedExactly("STR"));
    ASSERT_FALSE(proj.isFieldRetainedExactly("STR"));
    ASSERT_FALSE(proj.isFieldRetainedExactly("STR"));
    ASSERT_TRUE(proj.isFieldRetainedExactly("STR"));
}