TEST_F(QueryPlannerTest, CanIntersectBoundsOnSecondFieldWhenSharedPrefixIsMultikeyButHasElemMatch) {
    MultikeyPaths multikeyPaths{{0U}, {0U}};
    addIndex(BSON("STR" << 1), multikeyPaths);
    runQuery(fromjson("STR"));

    assertNumSolutions(2U);
    assertSolutionExists(
        "STR");
    assertSolutionExists(
        "STR"
        "STR");
}