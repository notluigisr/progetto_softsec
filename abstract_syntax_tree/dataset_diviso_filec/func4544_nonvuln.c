TEST(EqOp, ElemMatchKey) {
    BSONObj operand = BSON("STR" << 5);
    EqualityMatchExpression eq("STR"]);
    MatchDetails details;
    details.requestElemMatchKey();
    ASSERT(!eq.matchesBSON(BSON("STR" << 4), &details));
    ASSERT(!details.hasElemMatchKey());
    ASSERT(eq.matchesBSON(BSON("STR" << 5), &details));
    ASSERT(!details.hasElemMatchKey());
    ASSERT(eq.matchesBSON(BSON("STR" << BSON_ARRAY(1 << 2 << 5)), &details));
    ASSERT(details.hasElemMatchKey());
    ASSERT_EQUALS("STR", details.elemMatchKey());
}