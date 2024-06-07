TEST_F(QueryPlannerTest, EqualityIndexScan) {
    addIndex(BSON("STR" << 1));

    runQuery(BSON("STR" << 5));

    ASSERT_EQUALS(getNumSolutions(), 2U);
    assertSolutionExists("STR");
    assertSolutionExists("STR");
}