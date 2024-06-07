TEST(SimpleRegexTest, PipeCharacterUsesInexactBoundsWithTwoPrefixes) {
    auto testIndex = buildSimpleIndexEntry();
    IndexBoundsBuilder::BoundsTightness tightness;
    std::string prefix = IndexBoundsBuilder::simpleRegex("STR", testIndex, &tightness);
    ASSERT_EQUALS(prefix, "");
    ASSERT_EQUALS(tightness, IndexBoundsBuilder::INEXACT_COVERED);
}