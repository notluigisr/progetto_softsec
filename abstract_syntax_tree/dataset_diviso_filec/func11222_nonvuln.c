TEST(GtOp, ElemMatchKey) {
    BSONObj operand = BSON("STR" << 5);
    GTMatchExpression gt;
    ASSERT(gt.init("STR"]).isOK());
    MatchDetails details;
    details.requestElemMatchKey();
    ASSERT(!gt.matchesBSON(BSON("STR" << 4), &details));
    ASSERT(!details.hasElemMatchKey());
    ASSERT(gt.matchesBSON(BSON("STR" << 6), &details));
    ASSERT(!details.hasElemMatchKey());
    ASSERT(gt.matchesBSON(BSON("STR" << BSON_ARRAY(2 << 6 << 5)), &details));
    ASSERT(details.hasElemMatchKey());
    ASSERT_EQUALS("STR", details.elemMatchKey());
}