TEST_F(QueryPlannerTest, ExistsTrueOnUnindexedField) {
    addIndex(BSON("STR" << 1));

    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists("STR");
    assertSolutionExists("STR");
}