TEST_F(QueryPlannerTest, PrefixRegexCovering) {
    addIndex(BSON("STR" << 1));
    runQuerySortProj(fromjson("STR"));

    ASSERT_EQUALS(getNumSolutions(), 2U);
    assertSolutionExists(
        "STR"
        "STR");
    assertSolutionExists(
        "STR"
        "STR");
}