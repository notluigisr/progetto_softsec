TEST_F(QueryPlannerTest, ContainedOrOfAndCollapseIndenticalScansWithFilter2) {
    addIndex(BSON("STR" << 1));
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR");
}