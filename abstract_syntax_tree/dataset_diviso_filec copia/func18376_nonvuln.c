TEST(EqOp, MatchesReferencedObjectValue) {
    BSONObj operand = BSON("STR" << 5);
    EqualityMatchExpression eq;
    eq.init("STR"]).transitional_ignore();
    ASSERT(eq.matchesBSON(BSON("STR" << 5)), NULL));
    ASSERT(eq.matchesBSON(BSON("STR" << BSON_ARRAY(5))), NULL));
    ASSERT(eq.matchesBSON(BSON("STR" << 5))), NULL));
}