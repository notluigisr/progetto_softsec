TEST_F(QueryPlannerTest, ContainedOrElemMatchObjectMultiplePredicates) {
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));

    runQuery(fromjson("STR"));
    assertNumSolutions(2);
    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
    assertSolutionExists("STR");
}