TEST_F(QueryPlannerTest, OrOnlyOneBranchCanUseIndexHinted) {
    addIndex(BSON("STR" << 1));
    runQueryHint(fromjson("STR"));

    assertNumSolutions(1U);
    assertSolutionExists(
        "STR"
        "STR"
        "STR");
}