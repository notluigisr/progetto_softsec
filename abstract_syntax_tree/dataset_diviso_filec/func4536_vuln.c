TEST(IndexBoundsBuilderTest, TranslateNotEqualToNullShouldBuildExactBoundsIfIndexIsNotMultiKey) {
    BSONObj indexPattern = BSON("STR" << 1);
    auto testIndex = buildSimpleIndexEntry(indexPattern);

    BSONObj obj = BSON("STR" << BSONNULL));
    auto expr = parseMatchExpression(obj);

    OrderedIntervalList oil;
    IndexBoundsBuilder::BoundsTightness tightness;
    IndexBoundsBuilder::translate(
        expr.get(), indexPattern.firstElement(), testIndex, &oil, &tightness);

    
    ASSERT_EQUALS(oil.name, "STR");
    ASSERT_EQUALS(tightness, IndexBoundsBuilder::EXACT);
    assertBoundsRepresentNotEqualsNull(oil);
}