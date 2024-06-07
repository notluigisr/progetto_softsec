TEST_F(QueryPlannerTest, ElemMatchTwoFields) {
    addIndex(BSON("STR" << 1));
    addIndex(BSON("STR" << 1));
    runQuery(fromjson("STR"));

    ASSERT_EQUALS(getNumSolutions(), 3U);
    assertSolutionExists("STR");
    assertSolutionExists("STR");
    assertSolutionExists("STR");
}