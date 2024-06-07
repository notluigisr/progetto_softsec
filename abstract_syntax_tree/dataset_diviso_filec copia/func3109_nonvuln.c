TEST_F(QueryPlannerTest, MultikeySharedPrefixElemMatchNotShared) {
    
    addIndex(BSON("STR" << 1), true);
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
}