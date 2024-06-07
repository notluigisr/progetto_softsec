TEST(IndexBoundsBuilderTest, TranslateGtNumberMax) {
    auto testIndex = buildSimpleIndexEntry();
    BSONObj obj = BSON("STR" << numberMax));
    auto expr = parseMatchExpression(obj);
    BSONElement elt = obj.firstElement();
    OrderedIntervalList oil;
    IndexBoundsBuilder::BoundsTightness tightness;
    IndexBoundsBuilder::translate(expr.get(), elt, testIndex, &oil, &tightness);
    ASSERT_EQUALS(oil.name, "STR");
    ASSERT_EQUALS(oil.intervals.size(), 1U);
    ASSERT_EQUALS(Interval::INTERVAL_EQUALS,
                  oil.intervals[0].compare(
                      Interval(BSON("STR" << positiveInfinity), false, true)));
    ASSERT_EQUALS(tightness, IndexBoundsBuilder::EXACT);
}