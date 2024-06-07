TEST_F(QueryPlannerTest, IntersectCanBeVeryBig) {
    params.options = QueryPlannerParams::NO_TABLE_SCAN | QueryPlannerParams::INDEX_INTERSECTION;
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    runQuery(
        fromjson("STR"
                 "STR"
                 "STR"
                 "STR"
                 "STR"
                 "STR"
                 "STR"));

    assertNumSolutions(internalQueryEnumerationMaxOrSolutions.load());
}