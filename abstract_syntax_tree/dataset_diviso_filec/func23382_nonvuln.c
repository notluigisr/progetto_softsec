TEST(InMatchExpression, MatchesScalar) {
    BSONObj operand = BSON_ARRAY(5);
    InMatchExpression in("STR");
    std::vector<BSONElement> equalities{operand.firstElement()};
    ASSERT_OK(in.setEqualities(std::move(equalities)));

    ASSERT(in.matchesBSON(BSON("STR" << 5.0), NULL));
    ASSERT(!in.matchesBSON(BSON("STR" << 4), NULL));
}