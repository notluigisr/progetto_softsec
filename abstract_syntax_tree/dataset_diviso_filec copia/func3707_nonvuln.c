TEST_F(QueryPlannerTest, IntersectCompoundInsteadUnusedField2) {
    params.options = QueryPlannerParams::NO_TABLE_SCAN | QueryPlannerParams::INDEX_INTERSECTION;
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    runQuery(fromjson("STR"));

    assertNumSolutions(3U);
    assertSolutionExists(
        "STR"
        "STR");
    assertSolutionExists(
        "STR"
        "STR");
    assertSolutionExists(
        "STR"
        "STR");
}