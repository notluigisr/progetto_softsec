TEST_F(QueryPlannerTest, TypeArrayUsingStringAliasMustFetchAndFilter) {
    addIndex(BSON("STR" << 1));
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR");
}