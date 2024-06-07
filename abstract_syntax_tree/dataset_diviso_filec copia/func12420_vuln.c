TEST(IndexBoundsBuilderTest, TranslateNotEqualToNullShouldBuildInexactBoundsIfIndexIsMultiKey) {
    BSONObj indexPattern = BSON("STR" << 1);
    auto testIndex = buildSimpleIndexEntry(indexPattern);
    testIndex.multikey = true;

    BSONObj matchObj = BSON("STR" << BSONNULL));
    auto expr = parseMatchExpression(matchObj);

    OrderedIntervalList oil;
    IndexBoundsBuilder::BoundsTightness tightness;
    IndexBoundsBuilder::translate(
        expr.get(), indexPattern.firstElement(), testIndex, &oil, &tightness);

    ASSERT_EQUALS(oil.name, "STR");
    ASSERT_EQUALS(tightness, IndexBoundsBuilder::INEXACT_FETCH);
    assertBoundsRepresentNotEqualsNull(oil);
}