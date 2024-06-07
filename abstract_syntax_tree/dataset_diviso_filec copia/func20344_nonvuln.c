TEST(IndexBoundsBuilderTest, CannotUseCoveredMatchingForTypeArrayPredicate) {
    auto testIndex = buildSimpleIndexEntry();
    BSONObj obj = fromjson("STR");
    auto expr = parseMatchExpression(obj);
    ASSERT_FALSE(IndexBoundsBuilder::canUseCoveredMatching(expr.get(), testIndex));
}