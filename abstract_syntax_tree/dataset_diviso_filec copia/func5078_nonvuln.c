TEST_F(QueryPlannerTest, CannotTrimIxisectAndHashWithOrChild) {
    params.options = QueryPlannerParams::INDEX_INTERSECTION;
    params.options |= QueryPlannerParams::NO_TABLE_SCAN;

    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));

    runQuery(fromjson("STR"));

    assertNumSolutions(3U);

    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");

    assertSolutionExists(
        "STR"
        "STR");

    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
}