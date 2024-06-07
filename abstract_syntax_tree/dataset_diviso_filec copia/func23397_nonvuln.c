TEST_F(QueryPlannerTest, AllElemMatchCompound) {
    
    addIndex(BSON("STR" << 1), true);

    runQuery(
        fromjson("STR"
                 "STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR"
        "STR"
        "STR"
        "STR");
}