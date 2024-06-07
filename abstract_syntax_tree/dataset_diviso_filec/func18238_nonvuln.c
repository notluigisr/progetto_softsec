TEST_F(QueryPlannerTest, OrBelowElemMatchInexactCovered) {
    
    addIndex(BSON("STR" << 1), true);
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR");
}