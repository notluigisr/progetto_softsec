TEST_F(QueryPlannerTest, BasicLimitWithIndex) {
    addIndex(BSON("STR" << 1));

    runQuerySkipNToReturn(BSON("STR" << 5), 0, -5);

    ASSERT_EQUALS(getNumSolutions(), 2U);
    assertSolutionExists("STR");
    assertSolutionExists(
        "STR"
        "STR");
}