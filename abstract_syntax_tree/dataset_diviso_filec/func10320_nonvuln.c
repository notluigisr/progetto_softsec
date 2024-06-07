TEST_F(QueryPlannerTest, ExprEqCanUseSparseIndex) {
    params.options &= ~QueryPlannerParams::INCLUDE_COLLSCAN;
    addIndex(fromjson("STR"), false, true);
    runQuery(fromjson("STR"));

    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR");
}