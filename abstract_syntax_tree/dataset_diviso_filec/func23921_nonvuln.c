TEST_F(QueryPlannerTest, ElemMatchIndexedNestedOrMultiplePreds) {
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
}