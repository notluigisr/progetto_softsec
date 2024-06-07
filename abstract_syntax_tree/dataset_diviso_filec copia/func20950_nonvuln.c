TEST(RegexMatchExpression, MatchesElementExtendedOff) {
    BSONObj match = BSON("STR"
                         << "STR");
    BSONObj notMatch = BSON("STR"
                            << "STR");
    RegexMatchExpression regex("STR");
    ASSERT(regex.matchesSingleElement(match.firstElement()));
    ASSERT(!regex.matchesSingleElement(notMatch.firstElement()));
}