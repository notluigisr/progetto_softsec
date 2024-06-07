TEST(RegexMatchExpression, MatchesElementExact) {
    BSONObj match = BSON("STR"
                         << "STR");
    BSONObj notMatch = BSON("STR"
                            << "STR");
    RegexMatchExpression regex;
    ASSERT(regex.init("STR").isOK());
    ASSERT(regex.matchesSingleElement(match.firstElement()));
    ASSERT(!regex.matchesSingleElement(notMatch.firstElement()));
}