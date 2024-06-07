TEST_F(QueryPlannerTest,
       EmptyQueryWithProjectionDoesNotUseCoveredIxscanOnDotttedNonMultikeyIndexIfDisabled) {
    params.options &= ~QueryPlannerParams::GENERATE_COVERED_IXSCANS;
    addIndex(BSON("STR" << 1));
    runQueryAsCommand(fromjson("STR"));
    assertNumSolutions(1);
    assertSolutionExists(
        "STR"
        "STR");
}