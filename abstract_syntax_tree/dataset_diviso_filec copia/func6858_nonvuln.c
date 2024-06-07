TEST(SimpleRegexTest, RootedRegexCantBeIndexedTightlyIfIndexHasCollation) {
    CollatorInterfaceMock collator(CollatorInterfaceMock::MockType::kReverseString);
    auto testIndex = buildSimpleIndexEntry();
    testIndex.collator = &collator;

    IndexBoundsBuilder::BoundsTightness tightness;
    std::string prefix = IndexBoundsBuilder::simpleRegex("STR", testIndex, &tightness);
    ASSERT_EQUALS(prefix, "");
    ASSERT_EQUALS(tightness, IndexBoundsBuilder::INEXACT_FETCH);
}